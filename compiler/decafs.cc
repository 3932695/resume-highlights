#include "parsetree.h"
#include "semantics.h"
#include <assert.h>

extern int yyparse(void);
extern ParseTree * top;
extern S_interface* currentInterface;
extern S_class* currentClass;
extern S_function* currentFunction;
extern Symtab * currentScope;

template <typename A, typename B, typename C>
struct triple{
	A first;
	B second;
	C third;
};

vector<triple<string, string, int> > subsuprels;
int localVarCount;
S_class * temp;

void pass1(ParseTree * tree, bool declare = false);

void print(semantics * value){
	cout << "Name: " << value->name << 
	", Value: " << (value == NULL? "NULL" : value->kind()) <<
	((value != NULL && value->kind() == "S_variable")? ", Type: "+((S_variable*)value)->type->name : "") <<
	endl;
}

void printScope(){
	if(currentClass)
		cout << "CLASS: " << currentClass->name << endl;
	if(currentInterface)
		cout << "INTERFACE: " << currentInterface->name << endl;
	if(currentFunction)
		cout << "FUNCTION: " << currentFunction->name << endl;

	currentScope->printScope();
}


bool class_occurs(string subclass, string superclass) 
{
    if (subclass == superclass)
        return true;
    for (size_t i = 0; i < subsuprels.size();i++) 
        if (subsuprels[i].first == superclass)  
            return class_occurs(subclass, subsuprels[i].second);
    return false;
}

void semantic_error(string err, int line)
{
	cout << "Semantic error: " << err << " on line " << line << endl;
	exit(1);
}

void error_if_defined_locally(ParseTree *tree)
{

  // tree represents an identifier.  Make sure it's not already defined.
	assert(tree->type == TERMINAL and tree->token->type == Y_Identifier);
	string var_name = tree->token->text;		
	int lineno = tree->token->line;
	if (currentScope->local_lookup(var_name)){
		semantic_error(var_name + " already defined", lineno);
	}
}

string get_type_name(ParseTree *typetree)
{
  // Convert a tree representing a type to a string.
  // My descriptions for these always start with TYPE_.
  // Your mileage may vary.
  
  //cout << "In get type name with " << typetree->toString() << endl;
  // Arrays go to "[]",
  // User-defined things go to the identifier.
  // Built-ins are like TYPE_int, so strip off the TYPE_.
	if (typetree->description == "ARRAY:"){
		return get_type_name(typetree->children[0])+" []";
	}
	else {
		return typetree->token->text;
	}
}

int get_type(ParseTree *typetree)
{
  // Convert a tree representing a type to a string.
  // My descriptions for these always start with TYPE_.
  // Your mileage may vary.
  
  //cout << "In get type name with " << typetree->toString() << endl;
  // Arrays go to "[]",
  // User-defined things go to the identifier.
  // Built-ins are like TYPE_int, so strip off the TYPE_.
	if (typetree->description == "ARRAY:"){
		return get_type(typetree->children[0]);
	}
	else {
		return typetree->token->type;
	}
}


S_variable * makeVariable(ParseTree *tree)
{
	// In pass1, Create a S_variable object, and insert in the symbol table.
	// This is useful for formal parameters as well as
	// variable declarations in side Stmt blocks.  Your
	// parse tree may vary slightly, so tweak this as needed.
	// assert(tree->description == "VARIABLE");
	string type_name = get_type_name(tree->children[0]);
	string var_name = tree->children[1]->token->text;
	int lineNo = tree->children[1]->token->line;
	error_if_defined_locally(tree->children[1]);
	
	S_variable * entry = new S_variable;
	entry->name = var_name;
	entry->type = new S_type;
	entry->type->name = type_name;
	entry->variable_id = -7; // -7 is uninitialized 
	entry->parentClass = currentClass;

	
	currentScope->dict[var_name] = entry;
	return entry;
}

S_function * makeFunction(ParseTree *tree, bool prototype)
{
	string type_name = tree->children[0]->token->text;
	string func_name = tree->children[1]->token->text;
	ParseTree * formals = tree->children[2];
	ParseTree * stmtblck;
	if(!prototype)
		stmtblck = tree->children[3];
	
	S_function * entry = new S_function;
	entry->name = func_name;
	entry->returnType = new S_type;
	entry->returnType->name = "void";
	entry->parentClass = currentClass;
	
	error_if_defined_locally(tree->children[1]);
	if(type_name != "void"){
		entry->returnType->name = type_name;
	}
	
	
	openscope();
	currentFunction = entry;
	if(formals){
		for (size_t i = 0; i < formals->children.size();i++) {
			S_variable * formal = makeVariable(formals->children[i]);
			currentFunction->formals.push_back(formal);	

		}
	}
	
	if(!prototype)
		pass1(stmtblck);
	currentFunction = NULL;
	
	currentScope->dict[func_name] = entry;
	tree->symtab = closescope();

	
	return entry;
	
}

S_class * makeClass(ParseTree *tree)
{
	string class_name = tree->children[1]->token->text;
	int lineNo = tree->children[1]->token->line;
	ParseTree * extends = tree->children[2];
	ParseTree * implements = tree->children[3];
	ParseTree * fields = tree->children[4];
	
	
	
	S_class * entry = new S_class;
	entry->name = class_name;
	error_if_defined_locally(tree->children[1]);
	
	openscope();
	currentClass = entry;
	if(fields){
		for (size_t i = 0; i < fields->children.size();i++){
			pass1(fields->children[i]);
			entry->fields.push_back(currentScope->lookup(fields->children[i]->children[1]->token->text));
		}
	}
	//printScope(); // PRINT
	currentScope->dict[class_name] = entry;
	
	// NOTE: much more processing will be done with this later.
	
	if(extends){
		string super_name = extends->children[1]->token->text;
		if(currentScope->lookup(super_name) == NULL){
			semantic_error("extended super class not defined", lineNo);
		}
		if(class_occurs(class_name, super_name)){
			semantic_error("subclass name shared by higher class", lineNo);
		}else{
			entry->parentClass = (S_class*) currentScope->lookup(super_name);
			triple<string, string, int> subsuprel;
			subsuprel.first = class_name;
			subsuprel.second = super_name;
			subsuprel.third = lineNo;
			subsuprels.push_back(subsuprel);
		}
	}else{
		entry->parentClass = NULL;
	}
	
	
	currentClass = NULL;
	tree->symtab = closescope();
	return entry;
}

S_interface * makeInterface(ParseTree *tree)
{
	string interface_name = tree->children[1]->token->text;
	ParseTree * prototypes = tree->children[2];	
	S_interface * entry = new S_interface;
	entry->name = interface_name;
	error_if_defined_locally(tree->children[1]);
	
	
	openscope();
	currentInterface = entry;
	if(prototypes){
		for (size_t i = 0; i < prototypes->children.size();i++){
			S_function * prototype = makeFunction(prototypes->children[i], true);
			entry->functions.push_back(prototype);
			if(currentClass || currentFunction)
				currentScope->dict[entry->name] = entry;
		}
	}
	currentScope->dict[interface_name] = entry;
	
	//printScope(); // PRINT


	currentInterface = NULL;
	tree->symtab = closescope();
	return entry;
}



void pass1(ParseTree * tree, bool declare)
{
	if (!tree) return;
	if (tree->type==TERMINAL) return;
	// must be nonterminal
	if (tree->description=="==== DECLARATIONS ====") {

		openscope();

		for (size_t i = 0; i < tree->children.size();i++)
			pass1(tree->children[i], true);
		 // printScope(); // PRINT
		tree->symtab = closescope();
	}
	else if (tree->description=="STATEMENT BLOCK") {

		openscope();

		for (size_t i = 0; i < tree->children.size();i++)
			pass1(tree->children[i]);
		 // printScope(); // PRINT
		tree->symtab = closescope();
	}
	else if (tree->description == "VARIABLE"){

		S_variable * entry = makeVariable(tree);
		
		if(currentClass && !currentFunction){
			currentScope->dict[entry->name] = entry;
			tree->symtab = currentScope;
		}
		
		
	}
	
	else if (tree->description == "==== FUNCTION ===="){
		
		S_function * entry = makeFunction(tree, false);
		
		if(currentClass || currentFunction || declare){
			currentScope->dict[entry->name] = entry;
			//tree->symtab = currentScope;
		}
	
	}
	
	else if (tree->description == "==== CLASS ===="){
		S_class * entry = makeClass(tree);
		//currentScope->dict[entry->name] = entry;
		//tree->symtab = currentScope;
		if(tree->symtab){
			currentScope->dict[entry->name] = entry;
			//tree->symtab = currentScope;
		}
	}
	
	else if (tree->description == "==== INTERFACE ===="){
		S_interface * entry = makeInterface(tree);
		//currentScope->dict[entry->name] = entry;
		//tree->symtab = currentScope;
		if(tree->symtab){
			currentScope->dict[entry->name] = entry;
			//tree->symtab = currentScope;
		}
	}	
	else if (tree->type == NONTERMINAL){
		
		for (size_t i = 0; i < tree->children.size();i++)
			pass1(tree->children[i]);
	}
}

string stripBrackets(string result){
	
	string array_brackets = " []";
	int i = result.find(array_brackets);
	if(i != -1)
		return stripBrackets(result.erase(i, array_brackets.length()));
	else
		return result;

}



void pass2(ParseTree * tree){
	if (!tree) return;
	

	if(tree->symtab)
		currentScope = tree->symtab;
	if(tree->description == "VARIABLE"){
		string type = get_type_name(tree->children[0]);
		string nakedtype = stripBrackets(type);
		string identifier = tree->children[1]->token->text;
		int lineNo = tree->children[1]->token->line;

		
		if(get_type(tree->children[0]) == 280){ // if typeIdentifier
			if(!(currentScope->lookup(nakedtype))){
				semantic_error("type '" + nakedtype + "' is undefined", lineNo);
			}
			string semantic_type;
			Symtab * scope = currentScope;
			while(!(scope->local_lookup(nakedtype))){
				scope = scope->parent;
			}
			semantic_type = scope->dict[nakedtype]->kind();
			if (!(semantic_type == "S_interface" || semantic_type == "S_class"))
				semantic_error("type '" + nakedtype + "' is undefined", lineNo);
		}
		
			
		if(currentClass && currentFunction){
			((S_variable*)(currentScope->dict[identifier]))->variable_id = localVarCount + 1;
			localVarCount++;
		}else if(currentFunction){
			((S_variable*)(currentScope->dict[identifier]))->variable_id = localVarCount;
			localVarCount++;
		}
		else if(currentClass){
			((S_variable*)(currentScope->dict[identifier]))->variable_id = -1; // instance variable
		}
		else{
			((S_variable*)(currentScope->dict[identifier]))->variable_id = -2; // global variable
		}
		//printScope(); // PASS 2 PRINT
		
	}
	else if (tree->description == "==== FUNCTION ====" || tree->description == "PROTOTYPE"){
		localVarCount = 0;
		string identifier = tree->children[1]->token->text;
		ParseTree * formals = tree->children[2];
		ParseTree * stmtblck;
		
		if(tree->description == "==== FUNCTION ====")
			stmtblck = tree->children[3];
		
		S_function * entry = (S_function*)(currentScope->dict[identifier]);
	
		currentFunction = entry;
		
		if(formals){
			for (size_t i = 0; i < formals->children.size();i++) {
				pass2(formals->children[i]);
				currentScope = tree->symtab;
			}
		}
		
		if(tree->description == "==== FUNCTION ===="){
			pass2(stmtblck);
			currentScope = tree->symtab;
		}
		
		currentFunction = NULL;
		
	}else if (tree->description == "==== CLASS ===="){
		string identifier = tree->children[1]->token->text;
		int lineNo = tree->children[1]->token->line;
		ParseTree * extends = tree->children[2];
		ParseTree * implements = tree->children[3];
		ParseTree * fields = tree->children[4];
		S_class * entry = (S_class*)(currentScope->dict[identifier]);		
		currentClass = entry;
		
		
		if(fields){
			pass2(fields);
			currentScope = tree->symtab;
		}
		if(implements){
			implements = implements->children[1];
			
			for(size_t i = 0; i < implements->children.size();i++){
				
				string interface_name = implements->children[i]->token->text;
				if(!(currentScope->lookup(interface_name))){
					semantic_error("interface '" + interface_name + "' is undefined", lineNo);
				}
				
				string semantic_type;
				Symtab * scope = currentScope;
				while(!(scope->local_lookup(interface_name))){
					scope = scope->parent;
				}
				
				semantic_type = scope->dict[interface_name]->kind();
				if (!(semantic_type == "S_interface"))
					semantic_error("interface '" + interface_name + "' is undefined", lineNo);
				
				entry->interfaces.push_back((S_interface *)(scope->dict[interface_name]));
				
				vector<S_function*> prototypes = ((S_interface *)(scope->dict[interface_name]))->functions;
				
				for(int j = 0; j < prototypes.size(); j++){
					
					S_function * prototype = prototypes.at(j);
					string name = prototype->name;
					string returnType = prototype->returnType->name;
					int formalsCount =  prototype->formals.size();
					vector<S_variable *> proto_parameters = prototype->formals;
					S_function * class_implement;

					if(currentScope->local_lookup(name) == NULL){
						
						if(extends){
							S_class * superClass = (S_class*)(currentScope->lookup(currentClass->parentClass->name));
							bool found = false;
							
							for(int k = 0; k < superClass->fields.size(); k++){
								if(superClass->fields[k]->name == name){
									if(superClass->fields[k]->kind() == "S_function"){
										found = true;
										
										class_implement = (S_function*)(superClass->fields[k]);
										
									}
								}
									
							}
							
							if(!found)
								semantic_error("prototype '" + name + "' missing from class", lineNo);
						}else{
							semantic_error("prototype '" + name + "' missing from class", lineNo);
						}
					}else if(currentScope->local_lookup(name)->kind() != "S_function"){
					
						semantic_error("expected implementation of prototype '" + name + "' is a non-function", lineNo);
					}else{
						class_implement = (S_function*)currentScope->local_lookup(name);
					}
					

					vector<S_variable *> class_parameters = ((S_function *)(class_implement))->formals;

				
					if(prototype->returnType->name != class_implement->returnType->name){
						semantic_error("return type mismatch in implementation of prototype '" + name + "'", lineNo);
					}
					if(prototype->formals.size() != class_implement->formals.size()){
						semantic_error("parameter count mismatch in implementation of prototype '" + name + "'", lineNo);
					}
					for(int k = 0; k < class_parameters.size(); k++){
						S_variable * class_parameter = class_parameters.at(k);
						S_variable * proto_parameter = proto_parameters.at(k);
						if(class_parameter->type->name != proto_parameter->type->name){
							semantic_error("parameter type mismatch in implementation of prototype '" + name + "'", lineNo);
						}
					}
				}
				
			}
		}
		currentClass = NULL;
		
	}	
	else {
		for (size_t i = 0; i < tree->children.size();i++){
			if (tree->children[i] != NULL){
				pass2(tree->children[i]);
			}
		}
	}
	
	
}

bool checkParent(string t1, string t2, Symtab * scope){

	if(scope->lookup(t1) == NULL){
		return false;
	}
	if(scope->lookup(t1)->kind() == "S_interface"){
		
		//S_interface * interface = (S_interface*) scope->lookup(t1);
		S_class * superClass = (S_class*) scope->lookup(t2);
		while(superClass != NULL){
			for(int i = 0; i < superClass->interfaces.size(); i++){
				if(superClass->interfaces[i]->name == t1){
					return true;
				}
			}
			superClass = superClass->parentClass;
		}
		
	} else if (scope->lookup(t1)->kind() == "S_class"){
		S_class * subclass = (S_class*) scope->lookup(t1);
		while(subclass->parentClass != NULL){
			if(subclass->parentClass->name == t2){
				return true;
			}else{
				subclass = subclass->parentClass;
			}
		}
	}
	return false;
	
}

int checkClassFields(S_class * expr_class, string ident, string condition){
		vector<semantics *> fields = expr_class->fields;
		
		int pass = -1;
		for(int i = 0; i < fields.size(); i++){
			if((fields.at(i)->name == ident) && (fields.at(i)->kind() == condition)){
	
				pass = i;
			}
		}
		if (pass == -1){
			if(expr_class->parentClass != NULL){
				temp = expr_class->parentClass;
				
				return checkClassFields(expr_class->parentClass, ident, condition);
			}else{
				return -1;
			}
		}else{
			return pass;
		}
}

int checkInterfaceFunctions(S_interface * expr_interface, string ident, string condition){
		vector<S_function *> functions = expr_interface->functions;
		
		int pass = -1;
		for(int i = 0; i < functions.size(); i++){
			if((functions.at(i)->name == ident) && (functions.at(i)->kind() == condition)){
				pass = i;
			}
		}
		return pass;

}

void pass3(ParseTree * tree, Symtab * parentScope){
	if (!tree) return;
	if(tree->symtab)
		currentScope = tree->symtab;
	else
		currentScope = parentScope;
	
	if(tree->description == "==== CLASS ===="){
		string identifier = tree->children[1]->token->text;
		ParseTree * extends = tree->children[2];
		ParseTree * implements = tree->children[3];
		ParseTree * fields = tree->children[4];		
		S_class * entry = (S_class*)(currentScope->dict[identifier]);		

		currentClass = entry;
		
		if(extends){
			pass3(extends, currentScope);
			currentScope = tree->symtab;
		}
		if(implements){
			pass3(implements, currentScope);
			currentScope = tree->symtab;
		}
		if(fields){
			pass3(fields, currentScope);
			currentScope = tree->symtab;
		}
		currentClass = NULL;
	}else if (tree->description == "==== FUNCTION ===="){
		string identifier = tree->children[1]->token->text;
		ParseTree * formals = tree->children[2];
		ParseTree * stmtblck= tree->children[3];
		S_function * entry = (S_function*)(currentScope->dict[identifier]);
		
		currentFunction = entry;
		
		if(formals){
			pass3(formals, currentScope);
			currentScope = tree->symtab;
		}
		if(stmtblck){
			pass3(stmtblck, currentScope);
			currentScope = tree->symtab;
		}
		currentFunction = NULL;
	}else if (tree->description.substr(0, 5) == "bexpr"){
		string first;
		string second;
		int lineNo = tree->children[1]->token->line;
		string op = tree->children[1]->token->text;
		if(tree->children[0]->token)
			first = tree->children[0]->token->text;
		else
			first = tree->children[0]->description;
		if(tree->children[2]->token)
			second = tree->children[2]->token->text;
		else
			second = tree->children[2]->description;
		
		pass3(tree->children[0], currentScope);
		pass3(tree->children[2], currentScope);
		
		string t1 = tree->children[0]->stype;
		string t2 = tree->children[2]->stype;
		
		if(t1 == "" || t2 == ""){
			semantic_error("type undefined at variable", lineNo);
		}
		
		if(op == "="){
			if(t1 != t2){
				bool blarg = !(checkParent(t1, t2, currentScope) || checkParent(t2, t1, currentScope));
				if(blarg){
					semantic_error("type mismatch at assignment", lineNo);
				}
		
			}
			tree->stype = t1;
			// PRINT
			//cout << "(" << first << " @ " << tree->children[0]->stype << ")" << op << "(" << second << " @ " << tree->children[2]->stype << ")" << endl;
		}else if(op == "==" || op == "!="){
			if(t1 != t2){
				if(!(checkParent(t1, t2, currentScope) || checkParent(t2, t1, currentScope))){
					semantic_error("type mismatch between expressions", lineNo);
				}
			}
			tree->stype = "bool";
			// PRINT
			//cout << "(" << first << " @ " << tree->children[0]->stype << ")" << op << "(" << second << " @ " << tree->children[2]->stype << ")" << endl;
		}else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%"){
			if(!(t1 == "int" || t1 == "double")){
				semantic_error("expected int or double", lineNo);
			}
			if(t1 != t2){
				semantic_error("type mismatch between expressions", lineNo);
			}
			tree->stype = t1;
			// PRINT
			//cout << "(" << first << " @ " << tree->children[0]->stype << ")" << op << "(" << second << " @ " << tree->children[2]->stype << ")" << endl;
		}else if (op == "<" || op == "<=" || op == ">" || op == ">=") {
			if(!(t1 == "int" || t1 == "double")){
				semantic_error("expected int or double", lineNo);
			}
			if(t1 != t2){
				semantic_error("type mismatch between expressions", lineNo);
			}
			tree->stype = "bool";
			// PRINT
			//cout << "(" << first << " @ " << tree->children[0]->stype << ")" << op << "(" << second << " @ " << tree->children[2]->stype << ")" << endl;
		}else if (op == "&&" || op == "||"){
			if(t1 != "bool" || t2 != "bool"){
				semantic_error("expected bool", lineNo);
			}
			tree->stype = "bool";
			// PRINT
			//cout << "(" << first << " @ " << tree->children[0]->stype << ")" << op << "(" << second << " @ " << tree->children[2]->stype << ")" << endl;
		}
		
	}else if (tree->description.substr(0, 5) == "expr:"){
		pass3(tree->children[1], currentScope);
		string op = tree->children[0]->token->text;
		int lineNo = tree->children[0]->token->line;
		string t1 = tree->children[1]->stype;
		if(op == "-"){
			if(!(t1 == "int" || t1 == "double")){
				semantic_error("expected int or double", lineNo);
			}
			tree->stype = t1;
		}else if (op == "!"){
			if(t1 != "bool"){
				semantic_error("expected bool", lineNo);
			}
			tree->stype = "bool";
		}
	}else if(tree->description == "DOT"){
		ParseTree * expr = tree->children[0];
		ParseTree * ident = tree->children[1];
		int lineNo = expr->token->line;
		pass3(expr, currentScope);
		if(currentScope->lookup(expr->stype) == NULL){
			semantic_error("'" + expr->token->text + "' lacks a type", lineNo);
		}
		
		S_class * expr_class = (S_class *) currentScope->lookup(expr->stype);
		temp = expr_class;
		int condition = checkClassFields(expr_class, ident->token->text, "S_variable");
		S_class * final_class = temp;
		
		if( condition < 0){
			semantic_error("'" + ident->token->text + "' is not defined in '" + expr->token->text + "'", lineNo);
		}
		if(currentClass == NULL){
			if(currentClass != expr_class){
				semantic_error("'" + ident->token->text + "' cannot be accessed outside of its class", lineNo);
			}
		}
		pass3(ident, currentScope);
		ident->stype = ((S_variable*)final_class->fields.at(condition))->type->name;
		tree->stype = ident->stype;

	}else if (tree->description == "CALL: expr.ident(exprs)"){
		
		ParseTree * expr = tree->children[0]->children[0];
		ParseTree * ident = tree->children[0]->children[1];
		ParseTree * actuals = tree->children[1];
		
		int lineNo = ident->token->line;
		pass3(expr, currentScope);
		
		if(currentScope->lookup(expr->stype) == NULL){
			semantic_error("'" + expr->token->text + "' lacks a type", lineNo);
		}
		if(currentScope->lookup(expr->stype)->kind() == "S_class"){
			S_class * expr_class = (S_class *) currentScope->lookup(expr->stype);
			temp = expr_class;
			int condition = checkClassFields(expr_class, ident->token->text, "S_function");
			S_class * final_class = temp;
			if(condition < 0){
				semantic_error("'" + ident->token->text + "' is not defined in '" + expr->token->text + "'", lineNo);
			}
		
			pass3(ident, currentScope);
			
			tree->stype = ((S_function*)final_class->fields.at(condition))->returnType->name;
			
			if(actuals)
				pass3(actuals, currentScope);
		
			vector<S_variable*> formals = ((S_function*)final_class->fields.at(condition))->formals;
			
			if(formals.size() != ((actuals == NULL)? 0 : actuals->children.size())){
				semantic_error("parameter count mismatch at method call", lineNo);
				
			}
			for(int i = 0; i < formals.size(); i++){
				string actualType = actuals->children[i]->stype;
				string formalType = formals.at(i)->type->name;
				if(actualType != formalType){
					semantic_error("parameter type mismatch at method call", lineNo);
				}
			}
			
		}else if (currentScope->lookup(expr->stype)->kind() == "S_interface"){
			S_interface * expr_interface = (S_interface *) currentScope->lookup(expr->stype);
			int condition = checkInterfaceFunctions(expr_interface, ident->token->text, "S_function");
			if(condition <0){
				semantic_error("'" + ident->token->text + "' is not defined in '" + expr->token->text + "'", lineNo);
			}
			
			pass3(ident, currentScope);
			tree->stype = ((S_function*)expr_interface->functions.at(condition))->returnType->name;
			pass3(actuals, currentScope);
			vector<S_variable*> formals = ((S_function*)expr_interface->functions.at(condition))->formals;
			if(formals.size() != ((actuals == NULL)? 0 : actuals->children.size())){
				semantic_error("parameter count mismatch at method call", lineNo);
				
			}
			for(int i = 0; i < formals.size(); i++){
				string actualType = actuals->children[i]->stype;
				string formalType = formals.at(i)->type->name;
				if(actualType != formalType){
					semantic_error("parameter type mismatch at method call", lineNo);
				}
			}
			
		}
		
		
	}else if(tree->description == "CALL: ident(exprs)"){
		ParseTree * ident = tree->children[0];
		ParseTree * actuals = tree->children[1];
		string identifier = ident->token->text;
		int lineNo = ident->token->line;
		if(currentScope->lookup(identifier) == NULL || currentScope->lookup(identifier)->kind() != "S_function"){
			semantic_error("function '" + identifier + "' is undefined", lineNo);
		}
		S_function * function = (S_function*) currentScope->lookup(identifier);
		tree->stype = function->returnType->name;
		if(actuals)
			pass3(actuals, currentScope);
		vector<S_variable*> formals = function->formals;
		if(formals.size() != ((actuals == NULL)? 0 : actuals->children.size())){
			semantic_error("parameter count mismatch at function call", lineNo);
		}
		for(int i = 0; i < formals.size(); i++){
			string actualType = actuals->children[i]->stype;
			string formalType = formals.at(i)->type->name;
			if(actualType != formalType){
				semantic_error("parameter type mismatch at function call", lineNo);
			}
		}
	}else if (tree->description == "New(ident)"){
		ParseTree * ident = tree->children[1];
		string identifier = ident->token->text;
		int lineNo = ident->token->line;
		
		if(currentScope->lookup(identifier) == NULL){
			semantic_error("class '" + identifier + "' is undefined", lineNo);
		}else if (currentScope->lookup(identifier)->kind() != "S_class"){
			semantic_error("class '" + identifier + "' is undefined", lineNo);
		}
		
		tree->stype = identifier;
		
		
	}else if (tree->description == "ARRAY:"){
		pass3(tree->children[0], currentScope);
		tree->stype = tree->children[0]->stype + " []";
	}else if (tree->description == "NewArray(expr, type)"){
		int lineNo = tree->children[0]->token->line;
		ParseTree * typetree = tree->children[2];
		string type = typetree->token->text;
		pass3(tree->children[1], currentScope);
		
		if(tree->children[1]->stype != "int"){
			semantic_error("expected int at NewArray(int, type)", lineNo);
		}
		pass3(typetree, currentScope);
		if(currentScope->lookup(type) == NULL || currentScope->lookup(type)->kind() != "S_class"){
			if(typetree->stype == ""){
				semantic_error("class '" + type + "' is undefined", lineNo);
			}
		}
		tree->stype = type + " []";
		
	}else if (tree->description == "ARRAY: expr[expr]"){
		ParseTree * expr1 = tree->children[0];
		ParseTree * expr2 = tree->children[1];
		int lineNo = expr2->token->line;
		
		pass3(expr1, currentScope);
		pass3(expr2, currentScope);
		if(expr1->stype == ""){
			semantic_error("type undefined at variable", lineNo);
		}
		if(expr1->stype.find("[") == -1){
			semantic_error("variable is not an array type", lineNo);
		}
		if(expr2->stype != "int"){
			semantic_error("array index must be an int", lineNo);
		}
		tree->stype = expr1->stype.substr(0, expr1->stype.size()-3);
	}else if (tree->description.substr(0, 10) == "STATEMENT:"){
		ParseTree * cond = tree->children[1];
		ParseTree * stmtblck = tree->children[2];
		int lineNo = tree->children[0]->token->line;
		pass3(cond, currentScope);
		if(cond->stype != "bool"){
			semantic_error("condition must be a boolean", lineNo);
		}
		pass3(stmtblck, currentScope);
	}else if (tree->description == "RETURN"){
		ParseTree * result = tree->children[1];
		int lineNo = tree->children[0]->token->line;
		if(result)
			pass3(result, currentScope);
		if(result == NULL && currentFunction->returnType->name != "void"){
			semantic_error("missing return value", lineNo);
		}
		if(result->stype != currentFunction->returnType->name){
			semantic_error("return type mismatch", lineNo);
		}
	}else if (tree->description == "PRINT"){
		ParseTree * exprs = tree->children[1];
		
		int lineNo = tree->children[0]->token->line;
		pass3(exprs, currentScope);
		
		for(int i = 0; i < exprs->children.size(); i++){
			string t = exprs->children[i]->stype;
			if(!(t == "int" || t == "string" || t == "bool")){
				semantic_error("print only accepts int, string, and bool", lineNo);
			}
		}
		
	}else if (tree->description == "(expr?; expr; expr?)"){
		ParseTree * first = tree->children[0];
		ParseTree * second = tree->children[1];
		ParseTree * third = tree->children[2];

		int lineNo = tree->children[0]->children[0]->token->line;
		pass3(first, currentScope);
		pass3(second, currentScope);
		pass3(third, currentScope);
		
		
		if(!(first->stype == "int" && second->stype == "bool" && third->stype == "int")){
			semantic_error("invalid conditions for 'for statement'", lineNo);
		}
		
		tree->stype = "bool";
		
		
	}else if (tree->type == TERMINAL){
		string token = tree->token->toString();
		string tokentype = token.substr(2, token.find('(') - 2);
		int lineNo = tree->token->line;
		if(tokentype == "Identifier"){
			
			

			if(currentClass != NULL){

			}
			if(currentScope->lookup(tree->token->text)){
				
				semantics * identifier = currentScope->lookup(tree->token->text);
				if(identifier->kind() == "S_variable"){
					tree->stype = ((S_variable*)identifier)->type->name;
				}
			}else if(currentClass != NULL){
				temp = currentClass;
				S_variable * result;
				bool found = false;
				while(found == false){
					for(int i = 0; i < temp->fields.size(); i++){
						if(temp->fields[i]->name == tree->token->text && temp->fields[i]->kind() == "S_variable"){
								
							result = (S_variable*)temp->fields[i];
							found = true;
						}

			
					}
					if(temp->parentClass == NULL){
						break;
					}
					temp = temp->parentClass;

				}

				if(found){
					tree->stype = result->type->name;
				}
			}
		}else if(tokentype == "IntConstant"){
			tree->stype = "int";
		}else if(tokentype == "DoubleConstant"){
			tree->stype = "double";
		}else if(tokentype == "BoolConstant"){
			tree->stype = "bool";
		}else if(tokentype == "StringConstant"){
			tree->stype = "string";
		}else if(tokentype == "Int"){
			tree->stype = "int";
		}else if(tokentype == "Double"){
			tree->stype = "double";
		}else if(tokentype == "Bool"){
			tree->stype = "bool";
		}else if(tokentype == "String"){
			tree->stype = "string";	
		}else if(tokentype == "This"){
			if(currentClass == NULL){
				semantic_error("'this' must be called from within a class", lineNo);
			}
		}else if(tokentype == "Null"){
			tree->stype = "NULL";
		}
		//cout << token << " : " << tree->stype << endl; // PRINT
	}else if (tree->description == "STATEMENT BLOCK") {
		for (size_t i = 0; i < tree->children.size();i++){
			if (tree->children[i] != NULL){
				pass3(tree->children[i], currentScope);
			}
		}
	}else {
		for (size_t i = 0; i < tree->children.size();i++){
			
			if (tree->children[i] != NULL){
				pass3(tree->children[i], currentScope);

			}
		}
	}
		
}

/*

int main()
{
	yyparse();
	traverseTree(top,0,0);
	
	openscope();
	pass1(top);	
	pass2(top);
	pass3(top, currentScope);
	exit(0);
	return 0;
}

*/

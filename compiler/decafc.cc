#include "decafs.cc" 
#include <fstream>
#include <sstream>

extern FILE * yyin;

ofstream * currentFile;
ofstream * topClassFile;
int count;
stringstream sstm;
string classNameGlobal;
string decafSource;

void generate_block(ParseTree * block);
void generate_bool(ParseTree * expr);
void generate_statement(ParseTree * statement);
void generate(ParseTree * tree);

void generate_main_java_function(string mainClassName)
{
  *currentFile << ".method                  public static main([Ljava/lang/String;)V" << endl;
  *currentFile << "   .limit stack          0" << endl;
  *currentFile << "   .limit locals         1" << endl;
  *currentFile << "   invokestatic          " << mainClassName << "/main()V" << endl;
  *currentFile << "   return                " << endl;
  *currentFile << ".end method " << endl << endl;
}

string stripBracket(string result){
	
	string array_brackets = " []";
	int i = result.find(array_brackets);
	if(i != -1){
		count++;
		return stripBracket(result.erase(i, array_brackets.length()));
	}
	else
		return result;

}

string convertType(string type){
	count = 0;
	type = stripBracket(type);
	string newtype = classNameGlobal + "$" + type;
	if(currentClass && currentFunction){
		newtype = "L" + newtype + ";";
	}
	
	if(type == "int")
		newtype = "I";
	if(type == "double")
		newtype = "D";
	if(type == "string")
		newtype = "Ljava/lang/String;";
	if(type == "bool")
		newtype = "Z";
	if(type == "void")
		newtype = "V";
	if(count > 0){
		for(int i = 0; i < count; i++){
			newtype = "[" + newtype;
		}
	}
	
	
	
	return newtype;
}

void generate_globals(ParseTree * tree)
{
	
  if (!tree)
    return;
  //cout << "In generate with " << tree->description << endl;
  if (tree->description=="==== DECLARATIONS ===="){
	currentScope = tree->symtab;
	Dictionary dict = currentScope->dict;
	for(Dictionary::iterator i = dict.begin(); i != dict.end(); i++){
		semantics* value = i->second;
		if(value!= NULL && value->kind() == "S_variable"){
			int id = ((S_variable*)value)->variable_id;
			if(id == -2){
				string name = value->name;
				string type = ((S_variable*)value)->type->name;
				string newtype = convertType(type);
				*currentFile << ".field " << (currentClass == NULL? "static " : "") << name << " " << newtype << endl;
			}
		}
	}
	*currentFile << endl;
  }
  
  
  else{
	for (size_t i=0;i<tree->children.size();i++)
      generate_globals(tree->children[i]);
  }
	
}

void generate_instances(ParseTree * tree)
{
  if (!tree)
    return;
  //cout << "In generate with " << tree->description << endl;
  if (tree->description=="==== CLASS ===="){
 
	currentScope = tree->symtab;
	
	Dictionary dict = currentScope->dict;
	for(Dictionary::iterator i = dict.begin(); i != dict.end(); i++){
		semantics* value = i->second;
		if(value!= NULL && value->kind() == "S_variable"){
			int id = ((S_variable*)value)->variable_id;
			if(id == -1){
				string name = value->name;
				string type = ((S_variable*)value)->type->name;
				string newtype = convertType(type);
				*currentFile << ".field " << (currentClass == NULL? "static " : "") << name << " " << newtype << endl;
			}
		}
	}
	*currentFile << endl;
  }
  
  
  else{
	for (size_t i=0;i<tree->children.size();i++)
      generate_globals(tree->children[i]);
  }
	
}

void generate_preamble(string className, string superClassName, string decafSource)
{
  // write the jasmin header for a class.
  // superClassName might be the empty string if there is
  // no superclass.
  // 
  *currentFile	<< ".source " << decafSource << endl
				<< ".class public " << className << endl
				<< ".super " 
				<<  (superClassName==""?"java/lang/Object":superClassName)
				<< endl
				<< endl;
	//generate globals
	if(currentClass == NULL){
		generate_globals(top);
	}
	else{
	
		generate_instances(top);
     }
	 
    // constructor!
  *currentFile << ".method                  public <init>()V" << endl;
  *currentFile << ".limit stack          1" << endl;
  *currentFile << ".limit locals         1" << endl;
  *currentFile << "   aload_0" << endl;
  *currentFile << "   invokespecial " << (superClassName==""? "java/lang/Object/<init>()V":superClassName + "/<init>()V") << endl;
  *currentFile << "   return" << endl;
  *currentFile << ".end method" << endl;
}

string decaf_type(ParseTree * exprTree)
{
  // tree represents an expression  (actual parameter, rvalue, etc)
  // return the decaf type (string) determined
  // during pass 3 of semantic type-checking
  // FIXME:
  return exprTree->stype;
}

string jasmin_binop_instruction(string op, string type, ParseTree * expr)
{
	if (type=="int") {
		if (op=="+")
			return "iadd";
		if (op=="-")
			return "isub";
		if (op=="*")
			return "imul";
		if (op=="/")
			return "idiv";
		if (op=="%")
			return "irem";
	
    cout << "unimplemented binary operator " << op << " for type " << type << endl;
    exit(1);
  }
  cout << "unimplemented type " << type << " in jasmin_binop_instruction." << endl;
  exit(1);
}


string load_mnemonic(string typestr)
{
	// Given a type, return the correct store mnemonic (istore, dstore, astore)
	// FIXME!!  Right now only ints are allowed!!!

	if(typestr == "int")
		return "iload";
	if(typestr == "bool"){
		return "iload";
	}
	return "aload";

	cout << "unimplemented load mnemonic: " << typestr << endl;
	exit(1);
}

string store_mnemonic(string typestr)
{
  // Given a type, return the correct store mnemonic (istore, dstore, astore)
  // FIXME!!  Right now only ints are allowed!!!
  
	if(typestr == "int")
		return "istore";
	if(typestr == "bool")
		return "istore";
	return "astore";
		
  
	cout << "unimplemented store mnemonic: " << typestr << endl;
	exit(1);
}

void generate_variable_load(string varname)
{
	semantics * raw = currentScope->lookup(varname);
	if(raw->kind() == "S_variable"){
		S_variable *var=(S_variable *)currentScope->lookup(varname);
  // FIXME:  Current assumption, a local variable!
		if(var->variable_id >= 0){
			*currentFile << "   " 
						<< load_mnemonic(var->type->name) << " " 
						<< var->variable_id << endl;
		}else if(var->variable_id == -2){
			*currentFile << "   getstatic " << classNameGlobal << "/" << var->name 
						<< " " << convertType(var->type->name) << endl;
		}else if(var->variable_id == -1){
			*currentFile << "   getfield " << classNameGlobal << "$" << currentClass->name << "/" << var->name 
						<< " " << convertType(var->type->name) << endl;
		}
	}
	
  
  

}



void generate_expr(ParseTree * expr)
{
  // Post:  generate code that will compute expr and leave 
  // it on the stack.
  
  // terminals:
  if (expr->type==TERMINAL and expr->token->type==Y_IntConstant) {

    *currentFile << "   sipush " << expr->token->text << endl;
  }
  else if (expr->type==NONTERMINAL and expr->description.substr(0, 5) == "bexpr") {
	if(expr->stype == "bool"){
		generate_bool(expr);
	}else{
		generate_expr(expr->children[0]);
		generate_expr(expr->children[2]);
		*currentFile << "   " 
					 << jasmin_binop_instruction(expr->children[1]->token->text,
												 decaf_type(expr), expr->children[1])
					 << endl;
	}
  }
	else if (expr->type==NONTERMINAL and expr->description == "CALL: ident(exprs)") {
		generate_statement(expr);
	}
	else if (expr->type==NONTERMINAL and expr->description == "CALL: expr.ident(exprs)") {
		generate_statement(expr);
	}
	else if (expr->type==NONTERMINAL and expr->description == "DOT") {
		
	
		string first = expr->children[0]->token->text;
		string second = expr->children[1]->token->text;
		generate_variable_load(first);
		generate_variable_load(second);
		
		/*
		//string stype = expr->stype;
		
		//generate_expr(ident);
		*currentFile << "ASDF" << endl;	
		*/
		
	}
	else if (expr->type==NONTERMINAL and expr->description == "New(ident)") {
	
		string ident = expr->children[1]->token->text;
		*currentFile << "   new " << classNameGlobal << "$" << ident << endl;
		*currentFile << "   dup " << endl;
		*currentFile << "   invokespecial " << classNameGlobal << "$" << ident << "/<init>()V" << endl;
	
	}
	else if(expr->type==NONTERMINAL and expr->description == "NewArray(expr, type)"){
		generate_expr(expr->children[1]);
		*currentFile << "   newarray " << expr->children[2]->token->text << endl;
	}
	else if(expr->type==NONTERMINAL and expr->description == "ARRAY: expr[expr]"){
		generate_variable_load(expr->children[0]->token->text);
		*currentFile << "   sipush " << expr->children[1]->token->text << endl;
		*currentFile << "   iaload" << endl;
	}
	
  else if (expr->type==TERMINAL and expr->token->type==Y_Identifier) {
    generate_variable_load(expr->token->text);
  }
  else if (expr->type==TERMINAL and expr->token->type==Y_StringConstant){
		*currentFile << "   ldc " << expr->token->text << endl;
  }
  else {
    cout << "UNIMPLEMENTED in generate_expr : " << expr->description << endl;
	expr->token->print();
    exit(1);
  }
}

void generate_Print_expr(ParseTree * expr)
{
  // generates a print statement
  // for Print(expr).
  *currentFile << "   getstatic java/lang/System/out "
   "Ljava/io/PrintStream;" << endl;
  generate_expr(expr);
  *currentFile << "   invokevirtual java/io/PrintStream/print("
               << convertType(decaf_type(expr)) << ")V" << endl;
}


void generate_Print(ParseTree * printstmt) {
  ParseTree *exprs = printstmt->children[1];
  for (size_t i=0;i<exprs->children.size();i++) 
    generate_Print_expr(exprs->children[i]);
  // followed by a println...
  *currentFile << "   getstatic java/lang/System/out "
   "Ljava/io/PrintStream;" << endl;
  *currentFile << "   invokevirtual java/io/PrintStream/println()V" << endl;
}


string jasmin_formals(ParseTree * formals)
{
  // collect all the jasmin types of the 
  // formals into one string
  string answer = "";
  if(formals == NULL)
	return "()";
  for (size_t i=0;i<formals->children.size();i++) {
    ParseTree* var = formals->children[i];
    answer += convertType(get_type_name(var->children[0]));
  }
  return "(" + answer + ")";
}


void generate_bool(ParseTree * expr){

	string op = expr->children[1]->token->text;
	int line = expr->children[1]->token->line;

	if (op=="&&"){
		generate_expr(expr->children[0]);
		sstm.str("");
		sstm << "ifeq " << "AND_START" << line;
		*currentFile << "   " << sstm.str() << endl;
		generate_expr(expr->children[2]);
		sstm.str("");
		sstm << "ifeq " << "AND_START" << line;
		*currentFile << "   " << sstm.str() << endl;
		*currentFile << "   iconst_1" << endl;
		*currentFile << "   goto " << "AND_END" << line << endl;
		*currentFile << "AND_START" << line << ":" << endl;
		*currentFile << "   iconst_0" << endl;
		*currentFile << "AND_END" << line << ":" << endl;
	
	}else if (op=="||"){
		generate_expr(expr->children[0]);
		sstm.str("");
		sstm << "ifne " << "OR_START1" << line;
		*currentFile << "   " << sstm.str() << endl;
		generate_expr(expr->children[2]);
		sstm.str("");
		sstm << "ifeq " << "OR_START2" << line;
		*currentFile << "   " << sstm.str() << endl;
		
		*currentFile << "OR_START1" << line << ":" << endl;
		*currentFile << "   iconst_1" << endl;
		*currentFile << "   goto " << "OR_END" << line << endl;

		*currentFile << "OR_START2" << line << ":" << endl;
		*currentFile << "   iconst_0" << endl;
		*currentFile << "OR_END" << line << ":" << endl;
	
	}
	else{
		generate_expr(expr->children[0]);
		generate_expr(expr->children[2]);
	
		if (op=="<"){
			sstm.str("");
			sstm << "if_icmpge " << "LABEL" << line;
			
		}
		else if (op=="<="){
			sstm.str("");
			sstm << "if_icmpgt " << "LABEL" << line;
		}
		else if (op==">"){
			sstm.str("");
			sstm << "if_icmple " << "LABEL" << line;
		}
		else if (op==">="){
			sstm.str("");
			sstm << "if_icmplt " << "LABEL" << line;
		}
		else if (op=="=="){
			sstm.str("");
			sstm << "if_icmpne " << "LABEL" << line;
		}
		else if (op=="!="){
			sstm.str("");
			sstm << "if_icmpeq " << "LABEL" << line;
		}

		
		*currentFile << "   " << sstm.str() << endl;
		*currentFile << "   iconst_1" << endl;
		*currentFile << "   goto " << "END" << line << endl;
		*currentFile << "LABEL" << line << ":" << endl;
		*currentFile << "   iconst_0" << endl;
		*currentFile << "END" << line << ":" << endl;
	
	}
	
}


void generate_statement(ParseTree * statement)
{
	if (statement->description=="PRINT") {
		generate_Print(statement);
	} 
	else if (statement->description=="CALL: ident(exprs)"){
		ParseTree * ident = statement->children[0];
		ParseTree * actuals = statement->children[1];
		string identifier = ident->token->text;
		string stype = statement->stype;
		
		if(currentClass && identifier == currentFunction->name){
			*currentFile << "aload_0" << endl;
			
		}

		if(actuals){
			for(int i = 0; i < actuals->children.size(); i++){
				generate_expr(actuals->children[i]);
			}
			sstm.str("");
			for(int i = 0; i < actuals->children.size(); i++){
				sstm << convertType(actuals->children[i]->stype);
			}
			
			*currentFile << (currentClass == NULL? "    invokestatic " : "   invokevirtual ") 
						<< (currentClass == NULL? classNameGlobal : classNameGlobal + "$" + currentClass->name) << "/" << identifier 
						<< "(" << sstm.str() << ")" << convertType(stype) << endl;	
		}else{
			*currentFile << (currentClass == NULL? "    invokestatic " : "   invokevirtual ") 
						<< (currentClass == NULL? classNameGlobal : classNameGlobal + "$" + currentClass->name) << "/" << identifier 
						<< "()" << convertType(stype) << endl;	
		}
		
	}
	else if (statement->description=="CALL: expr.ident(exprs)"){
		ParseTree * expr = statement->children[0]->children[0];
		ParseTree * ident = statement->children[0]->children[1];
		ParseTree * exprs = statement->children[1];
		
		string identifier = ident->token->text;
		string stype = statement->stype;
		
		generate_expr(expr);
		
		if(exprs){
			for(int i = 0; i < exprs->children.size(); i++){
				generate_expr(exprs->children[i]);
			}
			sstm.str("");
			for(int i = 0; i < exprs->children.size(); i++){
				sstm << convertType(exprs->children[i]->stype);
			}
			
			*currentFile << "   invokevirtual " << convertType(expr->stype) 
						<< "/" << identifier <<"(" << sstm.str() << ")" << convertType(stype) << endl;	
		}else{
			*currentFile << "   invokevirtual " << convertType(expr->stype) 
						<< "/" << identifier <<"()" << convertType(stype) << endl;	
		
		}
		
		
	}
	else if (statement->description=="STATEMENT: for"){
		int line = statement->children[0]->token->line;
		ParseTree * conditions = statement->children[1];
		ParseTree * stmtblck = statement->children[2];
		
		generate_statement(conditions->children[0]);
		*currentFile << "FOR_START" << line << ":" << endl;
		generate_bool(conditions->children[1]);
		sstm.str("");
		sstm << "ifeq " << "FOR_END" << line;
		*currentFile << "   " << sstm.str() << endl;
		
		generate_block(stmtblck);
		generate_statement(conditions->children[2]);
		*currentFile << "   goto FOR_START" << line << endl;
		*currentFile << "FOR_END" << line << ":" << endl;
		
	}
	else if (statement->description=="STATEMENT: if"){
	
		
		int line = statement->children[0]->token->line;
		ParseTree * condition = statement->children[1];
		ParseTree * stmtblck = statement->children[2];
		
		generate_expr(condition);
		sstm.str("");
		sstm << "ifeq " << "IF_STMT" << line;
		*currentFile << "   " << sstm.str() << endl;
		if(stmtblck->description == "STATEMENT BLOCK"){
			generate_block(stmtblck);
		}else{
			generate_statement(stmtblck);
		}
	
		*currentFile << "IF_STMT" << line << ":" << endl;
	
	}
	else if (statement->description=="STATEMENT: while"){
		int line = statement->children[0]->token->line;
		ParseTree * condition = statement->children[1];
		ParseTree * stmtblck = statement->children[2];
		
		*currentFile << "WHILE_START" << line << ":" << endl;
		generate_expr(condition);
		sstm.str("");
		sstm << "ifeq " << "WHILE_EXIT" << line;
		*currentFile << "   " << sstm.str() << endl;
		generate_block(stmtblck);
		*currentFile << "   goto WHILE_START" << line << endl;
		*currentFile << "WHILE_EXIT" << line << ":" << endl;
		
	}
	else if (statement->description=="RETURN"){
		
		generate_expr(statement->children[1]);
		string returnType = currentFunction->returnType->name;
		
		if(returnType == "int")
			*currentFile << "   ireturn" << endl;
		if(returnType == "string")
			*currentFile << "   areturn" << endl;
		
		
	
	}
	
	else if (statement->description=="bexpr: lvalue = expr") {
    // assign a local variable.  FIXME: there is so much more possible.
    // Current assumptions:  It's a simple local variable.
		string stype = statement->children[2]->stype;
		
		if(statement->children[0]->description == "ARRAY: expr[expr]"){
			generate_expr(statement->children[0]->children[0]);
			generate_expr(statement->children[0]->children[1]);
			
		}
		
		if (stype == "bool"){
			generate_bool(statement->children[2]);
		}
		else{
			generate_expr(statement->children[2]);
		}
		
		if(statement->children[0]->description == "ARRAY: expr[expr]"){
			*currentFile << "   iastore" << endl;
		
		}else{
			S_variable * var =(S_variable *)currentScope->lookup(statement->children[0]->token->text);
		// generate something like: astore var-number

		
			if(var->variable_id >= 0){
				*currentFile << "   " << store_mnemonic(var->type->name) 
							<< " " << var->variable_id <<endl;
			}
			else if(var->variable_id == -2){
				*currentFile << "   putstatic " << classNameGlobal << "/" << var->name 
							<< " " << convertType(var->type->name) << endl;

			}
			else if(var->variable_id == -1){
				*currentFile << "   putfield " << classNameGlobal << "$" << currentClass->name << "/" << var->name 
							<< " " << convertType(var->type->name) << endl;
			}
		}
	
	} 

else// FIXME
    return;
}

void generate_block(ParseTree * block)
{
  Symtab *oldScope = currentScope;
  currentScope = block->symtab;
  
  ParseTree * statements = block->children[1];
  
  
  
	for (size_t i=0;i<statements->children.size();i++){
	
		if(currentClass)
			*currentFile << "   aload_0" << endl;
		generate_statement(statements->children[i]);
	}
  currentScope = oldScope;
  
}

void generate_class(ParseTree * classTree)
{
	
	currentScope = classTree->symtab;
	
	string className = classTree->children[1]->token->text;
	string superClassName = "";
	ParseTree * extends = classTree->children[2];
	
	currentClass = (S_class*)(currentScope->lookup(className));
	className = classNameGlobal + "$" + className;
	ParseTree * oldtop = top;

	top = classTree;
	
	currentFile = new ofstream((className + ".j").c_str());
	if(extends){
		superClassName = extends->children[1]->token->text;
		superClassName = classNameGlobal + "$" + superClassName;
		generate_preamble(className, superClassName, decafSource);
	}else{
		
		generate_preamble(className, "", decafSource);
	}
		
	generate(classTree->children[4]);
	currentFile = topClassFile;
	top = oldtop;
	currentClass = NULL;

}

void generate_function(ParseTree * function)
{
	
	currentScope = function->symtab;
	// generate a jasmin method.
	// it will be static if currentClass is NULL.
	string functionName = function->children[1]->token->text;
	

	S_function * sfunction = (S_function *)(currentScope->lookup(functionName));
	currentFunction = sfunction;
	string newtype = convertType(sfunction->returnType->name);
	
	*currentFile << ".method public " << (currentClass==NULL?"static ":" ")
               << functionName
			   << jasmin_formals(function->children[2])
			   << newtype
			   << endl;
	*currentFile << "   .limit stack 10" << endl; // FIXME
	*currentFile << "   .limit locals 10" << endl; // FIXME
	
	if(currentClass){
		if(jasmin_formals(function->children[2]) == "(L" + classNameGlobal + "$" + currentClass->name + ";)" ){
			*currentFile << "   aload_0" << endl;
		}
	}
	
	
	
	
	
	if(function->children[3])
		generate_block(function->children[3]);
  // need to generate a return here.
  // for void functions, it's easy.
  // for others???  Not so sure right now.
  // FIXME!!
	string returnType = sfunction->returnType->name;
	
	if(returnType == "void")
		*currentFile << "   return" << endl;
	
	
  
  
	*currentFile << ".end method" << endl << endl;  
	currentFunction = NULL;
}

void generate_interface(ParseTree * interface){

	
	
	string interfaceName = interface->children[1]->token->text;
	interfaceName = classNameGlobal + "$" + interfaceName;
	currentFile = new ofstream((interfaceName + ".j").c_str());
	*currentFile << ".source " << decafSource << endl;
	*currentFile << ".interface public abstract " << interfaceName << endl;
	*currentFile << ".super java/lang/Object" << endl;
				
    
	*currentFile << ".method      public abstract set" << jasmin_formals(interface->children[2]) << "V" << endl;
	*currentFile << ".end method" << endl;
	
	currentFile = topClassFile;
}

void generate(ParseTree * tree)
{
	if (!tree)
		return;
	//cout << "In generate with " << tree->description << endl;
	if (tree->description=="==== FUNCTION ====")
		generate_function(tree);
	else if (tree->description=="==== CLASS ===="){
		generate_class(tree);
	}else if (tree->description=="==== INTERFACE ===="){
		generate_interface(tree);
	}
	else{
		for (size_t i=0;i<tree->children.size();i++)
			generate(tree->children[i]);
	}
}

int main(int argc, char **argv)
{
  /* Make sure there's a given file name */
  if (argc != 2) {
    cout << "USAGE: " << argv[0] << " FILE" << endl;
    exit(1);
  }       
  yyin = fopen(argv[1], "r");
  /* and that it exists and can be read */
  if (!yyin) {
    cout << argv[1] << ": No such file or file can't be opened for reading."
         << endl;
    exit(1);
  }

  yyparse();
  currentClass = NULL;
  currentInterface = NULL;
  currentFunction = NULL;
  //traverseTree(top,0,0);

  // Semantics:

  currentScope = NULL;
  //openscope();
  pass1(top);
  pass2(top);
  pass3(top, currentScope);
 // top->symtab = closescope();
  traverseTree(top, 0,0);
  // Code generation
  
  string className = string(argv[1]);
  decafSource = className;
  className = "_" + className.substr(0,className.size()-6);  // strip .decaf

  topClassFile = new ofstream((className+".j").c_str());
  currentClass = NULL;
  currentFile = topClassFile;
  classNameGlobal = className;
  generate_preamble(className, "", decafSource);
  generate(top);
  generate_main_java_function(className);
	
  return 0;
}

/*
string decaf_type_to_jasmin_type(string tname)
{
  string array = "";
  
  
  // suck up the array type stuff...
  while (tname[tname.size()-1]==']') {
    array += "[";
    tname = tname.substr(0, tname.size()-3);
  }
  // convert from decaf builtin 
  // to jasmin/java builtin
  if (tname=="string")
    tname = "Ljava/lang/String;";
  else if (tname=="int") 
    tname = "I"; 
  else if (tname=="bool")
    tname = "Z";
  else if (tname=="double")
    tname = "D"; 
  else
    tname = "L" + tname + ";";
  return array + tname;
}
*/

/*
Symtab * restrictSemantic(Symtab * scope, string semanticType){
	Symtab * result;
	Dictionary dict = scope->dict;
	for(Dictionary::iterator i = dict.begin(); i != dict.end(); i++){
		semantics* value = i->second;
		string key = i->first;
		string name = value->name;
		string kind = value->kind();
		if(value!= NULL && value->kind() == "S_variable"){
			cout << 
			string type = ((S_variable*)value)->type->name;
			string id = ((S_variable*)value)->variable_id;
		}

}
*/

/*
string jasmin_type_from_tree(ParseTree * typetree)
{
  // typetree is a possibly NULL 
  // parsetree representing a type.
  // return the correct jasmin string for this type.

  if (!typetree)
    return "V";  // void if the tree is NULL

  return decaf_type_to_jasmin_type(get_type_name(typetree));
  
}
*/

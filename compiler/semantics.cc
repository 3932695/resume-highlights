#include <iostream>
#include <map>
#include <cassert>
#include <vector>

using namespace std;

#include "semantics.h"
#include "parsetree.h"


Symtab * currentScope = NULL;
S_interface* currentInterface = NULL;
S_class* currentClass = NULL;
S_function* currentFunction = NULL;
int currentSeq = 0;

Symtab::Symtab(Symtab *p) : parent(p) {}

semantics * Symtab::lookup(string key) { 
  semantics *answer;
  return 
    (answer = local_lookup(key)) ? answer : 
    parent ? parent->lookup(key) : NULL;

}

semantics * Symtab::local_lookup(string key) { 
	
	if(dict.count(key) > 0){	
		return dict[key];
	}
	return NULL;
}

void Symtab::insert(string key, semantics * item) {
  assert (local_lookup(key) == NULL);
  dict[key] = item;
}

void openscope()
{
  currentScope = new Symtab(currentScope);
}

void Symtab::printScope(){
	cout << "------------------------------------------------------" << endl;

	for(Dictionary::iterator i = dict.begin(); i != dict.end(); i++){
		semantics* value = i->second;
		cout << 
		"Key: " << i->first << 
		", Name: " << value->name <<
		", Value: " << (value == NULL? "NULL" : value->kind());
		
		if(value!= NULL && value->kind() == "S_variable"){
			cout << 
			", Type: " << ((S_variable*)value)->type->name <<
			", ID: " << ((S_variable*)value)->variable_id;
		}
		
		cout << endl;
	}

	cout << "------------------------------------------------------" << endl;
}



Symtab *closescope()
{
  Symtab *v = currentScope;
  currentScope = currentScope->parent;
  return v;
}


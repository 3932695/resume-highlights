#include <map>

struct S_class;

struct semantics {
	string name;
  // pure virtual function:
  virtual string kind() = 0;
  // at least one pure virtual function makes the class abstract 
  // (not instantiable.)

};

struct S_type : public semantics {
  virtual string kind() { return "S_type"; }
  // string name; // usually a decaf symbol, but sometimes 
  // a type.  name can't be void.
};

struct S_variable : public semantics {
	S_type * type;
	S_class * parentClass;
	int variable_id;
	virtual string kind() { return "S_variable"; }
};

struct S_function : public semantics {
	virtual string kind() { return "S_function"; }
	S_class * parentClass;
	vector<S_variable *> formals;
	S_type * returnType;  // NULL for a void function
};

struct S_interface : public semantics {
  virtual string kind() { return "S_interface"; }
  vector<S_function *> functions;
};

struct S_class : public semantics {
  virtual string kind() { return "S_class"; }
  S_class * parentClass;  // extends 
  vector<S_interface *> interfaces; // implements
  vector<semantics *> fields;  // each has to be S_function or S_variable
};

struct S_builtin : public semantics {
  virtual string kind() { return "S_builtin"; }
};


typedef map <string, semantics *> Dictionary;

struct Symtab {
  // A class to represent symbol tables
  // Chained togeher to represent nested scopes.
 public:
	Dictionary dict;
	Symtab(Symtab *p);
	semantics * lookup(string key);
	semantics * local_lookup(string key);
	semantics * print();
  
	void printScope();
	void insert(string key, semantics * item);

	Symtab * parent;  // outer scope
};

Symtab *closescope();
void openscope();

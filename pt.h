/*
 * pt.h
 */

#ifndef PT_H_
#define PT_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "parse.h"
#include "lex.h"
#include "val.cpp"

class Pt {
protected:
	int	linenum;
	Pt	*left;
	Pt	*right;

public:
	Pt(int linenum, Pt *l = 0, Pt *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~Pt() {
		delete left;
		delete right;
	}

	int GetLineNumber() const { return linenum; }

	Pt* getLeft(){
		return left;
	}
	Pt* getRight(){
		return right;
	}

  virtual bool isPlus() const { return false; }
  virtual bool isEq() const { return false; }
	virtual bool isIdent() const { return false; }
	virtual bool isVar() const { return false; }
	virtual string getId() const { return ""; }

	// forces all subclasses to implement Eval
	virtual Value Eval(unordered_map<string,Value>& symbolTable)=0;

	friend ostream& operator<<(ostream& out, const Pt* tree);
};

class StmtList : public Pt {
public:
	StmtList(Pt *l, Pt *r) : Pt(0, l, r) {}
	string getId() const { return "StmtList"; }

	// evaulates left and right
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value v = Value();
		if(getLeft() != 0){
			v = getLeft()->Eval(symbolTable);
		}
		if(getRight() != 0){
			v = getRight()->Eval(symbolTable);
			return v;
		}
		return v;
	}
};

class Print : public Pt {
public:
	Print(int line, Pt *e) : Pt(line, e) {}
	string getId() const { return "Print"; }

	// prints the left
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value v = getLeft()->Eval(symbolTable);
		cout << v;
		return v;
	}
};

class Println : public Pt {
public:
	Println(int line, Pt *e) : Pt(line, e) {}
	string getId() const { return "Println"; }

	// prints the left and goes to a new line
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value v = getLeft()->Eval(symbolTable);
		cout << v << endl;
		return v;
	}
};

class Repeat : public Pt {
public:
	Repeat(int line, Pt *i, Pt *e) : Pt(line, i, e) {}
	string getId() const { return "Repeat"; }

	// repeats an expression a certain amount of times
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value numRepeat = getLeft()->Eval(symbolTable);
		try{
			if(numRepeat.GetInt() < 0){
				throw "error";
			}
		}
		catch(const char* e){
			cerr << "RUNTIME ERROR: Cannot repeat negative number of times" << endl;
		}
		for(int i = 0; i < numRepeat.GetInt(); i++){
			Value v = getRight()->Eval(symbolTable);
		}
		return Value();
	}
};

class Assign : public Pt {
public:
	Assign(int line, Pt *l, Pt *r) : Pt(line, l, r) {}
	bool isEq() const { return true; }
	string getId() const { return "="; }

	// evaluates the right and assigns it to the left
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value rVal = getRight()->Eval(symbolTable);
		symbolTable[getLeft()->getId()] = rVal;
		return rVal;
	}
};

class PlusExpr : public Pt {
public:
	PlusExpr(int line, Pt *l, Pt *r) : Pt(line, l, r) {}
	bool isPlus() const { return true; }
	string getId() const { return "+"; }

	// evaluates the left and right and returns the sum
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value lVal = getLeft()->Eval(symbolTable);
		Value rVal = getRight()->Eval(symbolTable);
		return lVal + rVal;
	}
};

class MinusExpr : public Pt {
public:
	MinusExpr(int line, Pt *l, Pt *r) : Pt(line, l, r) {}
	string getId() const { return "-"; }

	// evaluates the left and right and subtracts the right from the left
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value lVal = getLeft()->Eval(symbolTable);
		Value rVal = getRight()->Eval(symbolTable);
		return lVal - rVal;
	}
};

class TimesExpr : public Pt {
public:
	TimesExpr(int line, Pt *l, Pt *r) : Pt(line, l, r) {}
	string getId() const { return "*"; }

	// evaluates the left and right and returns the product
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value lVal = getLeft()->Eval(symbolTable);
		Value rVal = getRight()->Eval(symbolTable);
		return lVal * rVal;
	}
};

class DivideExpr : public Pt {
public:
	DivideExpr(int line, Pt *l, Pt *r) : Pt(line, l, r) {}
	string getId() const { return "/"; }

	// evaluates the left and right and returns the quotient
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		Value lVal = getLeft()->Eval(symbolTable);
		Value rVal = getRight()->Eval(symbolTable);
		return lVal / rVal;
	}
};

class IConst : public Pt {
	int val;

public:
	IConst(Tok& t) : Pt(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
	string getId() const { return to_string(val); }

	// returns val
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		return Value(val);
	}
};

class SConst : public Pt {
	string val;

public:
	SConst(Tok& t) : Pt(t.GetLinenum()) {
		val = t.GetLexeme();
	}
	string getId() const { return val; }

	// returns val
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		return Value(val);
	}
};

class Ident : public Pt {
	string name;

public:
	Ident(Tok &t) : Pt(t.GetLinenum()) {
		name = t.GetLexeme();
	}
	bool isIdent() const { return true; }
	bool isVar() const { return true; }
	string getId() const { return name; }

	// returns val
	Value Eval(unordered_map<string,Value>& symbolTable){
		//cout << getId() << endl;
		if(symbolTable.find(name) == symbolTable.end()){
			throw "UNDECLARED VARIABLE " + name + "\n";
			return Value();
		}
		else{
			return Value(symbolTable[name]);
		}
	}
};

#endif /* PT_H_ */

#include <iostream>
#include <string>
#include "val.h"
using namespace std;

// overriding the + operator
Value Value :: operator+(const Value& op) const{
    if(this->IsInt() && op.IsInt()){
      return Value(this->GetInt() + op.GetInt());
    }
    else if(this->IsStr() && op.IsStr()){
      return Value(this->GetStr() + op.GetStr());
    }
    else{
      try{
        throw "error";
        return Value();
      }
      catch(const char* e){
        cerr << "RUNTIME ERROR: Operator '+' not defined between int and string" << endl;
        exit(0);
      }
    }
}

// overriding the - operator
Value Value :: operator-(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    return Value(this->GetInt() - op.GetInt());
  }
  else if(this->IsStr() && op.IsStr()){
    string thisStr = this->GetStr();
    string opStr = op.GetStr();
    int loc = thisStr.find(opStr);
    string returnStr = "";
    if(loc != -1){
      returnStr = thisStr.substr(0, loc) + thisStr.substr(loc+opStr.length());
      return Value(returnStr);
    }
    return Value(thisStr);
  }
  else{
    try{
      throw "error";
      return Value();
    }
    catch(const char* e){
      cerr << "RUNTIME ERROR: Operator '-' not defined between int and string" << endl;
      exit(0);
    }
  }
}

// overriding the * operator
Value Value :: operator*(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    return Value(this->GetInt() * op.GetInt());
  }
  else if(this->IsInt() && op.IsStr()){
    if(this->GetInt() < 0){
      try{
        throw "error";
        return Value();
      }
      catch(const char* e){
        cerr << "RUNTIME ERROR: Negative string multiplication not defined" << endl;
        exit(0);
      }
    }
    string returnStr = "";
    for(int i = 0; i < this->GetInt(); i++){
      returnStr += op.GetStr();
    }
    return Value(returnStr);
  }
  else if(this->IsStr() && op.IsInt()){
    if(op.GetInt() < 0){
      try{
        throw "error";
        return Value();
      }
      catch(const char* e){
        cerr << "RUNTIME ERROR: Negative string multiplication not defined" << endl;
        exit(0);
      }
    }
    string returnStr = "";
    for(int i = 0; i < op.GetInt(); i++){
      returnStr += this->GetStr();
    }
    return Value(returnStr);
  }
  else{
    try{
      throw "error";
      return Value();
    }
    catch(const char* e){
      cerr << "RUNTIME ERROR: Operator '*' not defined between string and string" << endl;
      exit(0);
    }
  }
}

// overriding the / operator
Value Value :: operator/(const Value& op) const{
  if(this->IsInt() && op.IsInt()){
    if(op.GetInt() == 0){
      try{
        throw "error";
        return Value();
      }
      catch(const char* e){
        cerr << "RUNTIME ERROR: Division by 0 not defined" << endl;
        exit(0);
      }
    }
    else{
      return Value(this->GetInt()/op.GetInt());
    }
  }
  else{
    try{
      throw "error";
      return Value();
    }
    catch(const char* e){
      cerr << "RUNTIME ERROR: Operator '/' not defined for strings" << endl;
      exit(0);
    }
  }
}

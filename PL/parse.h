/*
 * parse.h
 */
#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#include "lex.h"
#include "pt.h"

extern Pt *Prog(vector<Tok> &v);
extern Pt *Sl(vector<Tok> &v);
extern Pt *Stmt(vector<Tok> &v);
extern Pt *PrintStmt(vector<Tok> &v);
extern Pt *PrintlnStmt(vector<Tok> &v);
extern Pt *RepeatStmt(vector<Tok> &v);
extern Pt *Expr(vector<Tok> &v);
extern Pt *Sum(vector<Tok> &v);
extern Pt *Prod(vector<Tok> &v);
extern Pt *Primary(vector<Tok> &v);

void toString(Pt *tree, string &str){
  if(tree == 0){
    return;
  }
  toString(tree->getLeft(), str);
  str += tree->getId() + " ";
  toString(tree->getRight(), str);
}

ostream& operator<<(ostream& out, Pt* tree){
  string str = "";
  toString(tree, str);
  out << str;
  return out;
}

bool variableCheck(Pt* tree, unordered_map<string,Value>& m){
  if(tree->getId() == "="){
    if(variableCheck(tree->getRight(), m)){
      m[tree->getLeft()->getId()] = tree->getRight()->Eval(m);
    }
    else{
      return false;
    }
  }
  if(tree->getLeft() != 0){
    if(!variableCheck(tree->getLeft(), m)){
      return false;
    }
  }
  if(tree->isIdent()){
    string s = tree->getId();
    if(m.find(s) == m.end()){
      cout << "UNDECLARED VARIABLE " << s << endl;
      return false;
    }
  }
  if(tree->getRight() != 0){
    if(!variableCheck(tree->getRight(), m)){
      return false;
    }
  }
  return true;
}

int plusCount(Pt* tree){
  int total = 0;
  if(tree->isPlus()){
    total += 1;
  }
  if(tree->getLeft() != 0){
    total += plusCount(tree->getLeft());
  }
  if(tree->getRight() != 0){
    total += plusCount(tree->getRight());
  }
  return total;
}

int eqCount(Pt* tree){
  int total = 0;
  if(tree->isEq()){
    total += 1;
  }
  if(tree->getLeft() != 0){
    total += eqCount(tree->getLeft());
  }
  if(tree->getRight() != 0){
    total += eqCount(tree->getRight());
  }
  return total;
}

int maxDepth(Pt* tree){
  int leftDepth = 0;
  int rightDepth = 0;
  if(tree->getLeft() != 0){
    leftDepth = maxDepth(tree->getLeft());
  }
  if(tree->getRight() != 0){
    rightDepth = maxDepth(tree->getRight());
  }
  return 1+max(leftDepth, rightDepth);
}

#endif /* PARSE_H_ */

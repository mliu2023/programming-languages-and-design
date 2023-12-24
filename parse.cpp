/*
 * parse.cpp
 */
#include "parse.h"
#include "LexicalAnalyzer.cpp"
#include <fstream>
void ParseError(int line, string message){
  cerr << line << ": " << message << endl;
  exit(0);
}
Token GetNextToken(vector<Tok>& v){
  Tok t = v[0];
  v.erase(v.begin());
  return t.GetToken();
}
Token PeekNextToken(vector<Tok>& v){
  return v[0].GetToken();
}
int GetLine(vector<Tok>& v){
  return v[0].GetLinenum();
}
bool isDone(vector<Tok>& v){
  if(v[0].GetToken() == ::DONE){
    return true;
  }
  return false;
}
bool isEnd(vector<Tok>& v){
  if(v[0].GetToken() == ::END){
    return true;
  }
  return false;
}
Pt *Prog(vector<Tok> &v){
  int l = GetLine(v);
  Pt *tree = Sl(v);
  l = GetLine(v);
  if(tree == 0){
    delete tree;
    ParseError(l, "No statements in program");
    return 0;
  }
  return tree;
}
Pt *Sl(vector<Tok> &v){
  if(isDone(v)){
    return new StmtList(0, 0);
  }
  if(isEnd(v)){
    return new StmtList(0, 0);
  }
  int l = GetLine(v);
  Pt *tree;
  if(PeekNextToken(v) == ::SC){
    GetNextToken(v);
    tree = Sl(v);
    if(tree == 0){
      delete tree;
      return 0;
    }
  }
  else{
    tree = Stmt(v);
    if(tree == 0){
      delete tree;
      return 0;
    }
    if(PeekNextToken(v) != ::SC){
      l = GetLine(v);
      delete tree;
      ParseError(l, "Missing semicolon");
      return 0;
    }
    else{
      GetNextToken(v);
    }
  }
  return new StmtList(tree, Sl(v));
}
Pt *Stmt(vector<Tok> &v){
  Pt *tree;
  Token t = PeekNextToken(v);
  if(t == ::PRINT){
    GetNextToken(v);
    return PrintStmt(v);
  }
  else if(t == ::PRINTLN){
    GetNextToken(v);
    return PrintlnStmt(v);
  }
  else if(t == ::REPEAT){
    GetNextToken(v);
    return RepeatStmt(v);
  }
  else{
    return Expr(v);
  }
}
Pt *PrintStmt(vector<Tok> &v){
  int l = GetLine(v);
	Pt *tree = Expr(v);
  l = GetLine(v);
	if(tree == 0) {
    delete tree;
		ParseError(l, "Missing expression after print");
    return 0;
	}
	return new Print(l, tree);
}
Pt *PrintlnStmt(vector<Tok> &v){
  int l = GetLine(v);
  Pt *tree = Expr(v);
  l = GetLine(v);
  if(tree == 0){
    delete tree;
    ParseError(l, "Missing expression after println");
    return 0;
  }
  return new Println(l, tree);
}
Pt *RepeatStmt(vector<Tok> &v){
  int l;
  Pt *tree = Expr(v);
  if(tree == 0){
    return 0;
  }
  l = GetLine(v);
  if(GetNextToken(v) != ::BEGIN){
    delete tree;
    ParseError(l, "Missing BEGIN");
    return 0;
  }
  Pt *tree2 = Sl(v);
  if(tree2 == 0){
    delete tree;
    return 0;
  }
  l = GetLine(v);
  if(GetNextToken(v) != ::END){
    delete tree;
    ParseError(l, "Missing END");
  }
  return new Repeat(l, tree, tree2);
}
Pt *Expr(vector<Tok> &v){
  int l = v[0].GetLinenum();
  Pt *tree = Sum(v);
  if(tree == 0){
    return 0;
  }
  if(PeekNextToken(v) == ::EQ){
    GetNextToken(v);
    Pt *tree2 = Sum(v);
    if(tree2 == 0){
      return 0;
    }
    return new Assign(l, tree, tree2);
  }
  else{
    return tree;
  }
}
Pt *Sum(vector<Tok> &v){
  int l = v[0].GetLinenum();
  Pt *tree = Prod(v);
  if(PeekNextToken(v) == ::PLUS || PeekNextToken(v) == ::MINUS){
    Token t = PeekNextToken(v);
    GetNextToken(v);
    Pt *tree2 = Sum(v);
    if(tree2 == 0){
      return 0;
    }
    if(t == ::PLUS){
      return new PlusExpr(l, tree, tree2);
    }
    else{
      return new MinusExpr(l, tree, tree2);
    }
  }
  else{
    return tree;
  }
}
Pt *Prod(vector<Tok> &v){
  int l = v[0].GetLinenum();
  Pt *tree = Primary(v);
  Token t = PeekNextToken(v);
  if(t == ::STAR || t == ::SLASH){
    GetNextToken(v);
    Pt *tree2 = Prod(v);
    if(tree2 == 0){
      return 0;
    }
    else if(t == ::STAR){
      return new TimesExpr(l, tree, tree2);
    }
    else{
      return new DivideExpr(l, tree, tree2);
    }
  }
  else{
    return tree;
  }
}
Pt *Primary(vector<Tok> &v){
  int l = GetLine(v);
  Pt *tree;
  if(PeekNextToken(v) == ::IDENT){
    Tok t = v[0];
    v.erase(v.begin());
    return new Ident(t);
  }
  else if(PeekNextToken(v) == ::ICONST){
    Tok t = v[0];
    v.erase(v.begin());
    return new IConst(t);
  }
  else if(PeekNextToken(v) == ::SCONST){
    Tok t = v[0];
    v.erase(v.begin());
    return new SConst(t);
  }
  else{
    if(GetNextToken(v) != ::LPAREN){
      delete tree;
      ParseError(l, "Missing left parenthesis");
    }
    tree = Expr(v);
    if(tree == 0){
      return 0;
    }
    l = GetLine(v);
    if(GetNextToken(v) != ::RPAREN){
      delete tree;
      ParseError(l, "Missing right parenthesis");
    }
    return tree;
  }
}

int main(int argc, char *argv[]){
  vector<Tok> tokArr = tokenize(string(argv[1]));

  /*
  for(int i = 0; i < tokArr.size(); i++){
    cout << tokArr[i] << endl;
  }
  */

  Pt* tree = Prog(tokArr);
  //cout << tree << endl;
  unordered_map<string,Value> m;
  unordered_map<string,Value> n;
  if(!variableCheck(tree, m)){
    exit(0);
  }
  //cout << variableCheck(tree, m) << endl;
  //cout << "PLUS COUNT: " << plusCount(tree) << endl;
  //cout << "EQ COUNT: " << eqCount(tree) << endl;
  //cout << "MAX DEPTH: " << maxDepth(tree) << endl;
  tree->Eval(n);
}

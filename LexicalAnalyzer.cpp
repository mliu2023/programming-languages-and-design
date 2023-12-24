/*
 * LexicalAnalyzer.cpp
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "lex.h"
using namespace std;

string numToToken[18] = {"PRINT", "PRINTLN", "REPEAT", "BEGIN", "END",
"IDENT", "ICONST", "SCONST", "PLUS", "MINUS", "STAR", "SLASH", "EQ",
"LPAREN", "RPAREN", "SC", "ERR", "DONE"};

vector<Tok> getNextToken(istream& in, int& linenum){
	vector<Tok> tokens; // vector of Toks
	vector<string> arr; // vector of strings
	string str; // str will store a line
	getline(in, str); // get line from the istream
	// the regex pattern to match (comments, SCONST|ID, keywords|ICONST|Operators, SC, Parens|anything else (will cause an error))
	regex match("(//)|\"([^\"]*)\"|[a-zA-Z][a-zA-Z0-9]*|\\d+|[/;=\\-\\+\\*\\(\\):-@!-'[-`{-~]");
	regex_token_iterator<string::iterator> rend;
	//iterator add
	regex_token_iterator<string::iterator> t(str.begin(), str.end(), match);
	//add to vector
	while(t != rend){arr.push_back(t->str()); t++;}

	for(int j = 0; j < arr.size(); j++){
		if(arr[j] == "//"){
			break;
		}
		else if(arr[j] == "-"){
			if(j > 0 && (regex_match(arr[j-1], regex("[\\+\\*\\-=/]"))) && j < arr.size()-1 && regex_match(arr[j+1], regex("\\d+"))){
				tokens.push_back(Tok(::ICONST, arr[j]+arr[j+1], linenum));
				j++;
			}
			else if(j == 0){
				tokens.push_back(Tok(::ICONST, arr[j]+arr[j+1], linenum));
				j++;
			}
			else{
				tokens.push_back(Tok(::MINUS, arr[j], linenum));
			}
		}
		else if(arr[j] == "+"){tokens.push_back(Tok(::PLUS, arr[j], linenum));}
		else if(arr[j] == "*"){tokens.push_back(Tok(::STAR, arr[j], linenum));}
		else if(arr[j] == "/"){tokens.push_back(Tok(::SLASH, arr[j], linenum));}
		else if(arr[j] == "="){tokens.push_back(Tok(::EQ, arr[j], linenum));}
		else if(arr[j] == "("){tokens.push_back(Tok(::LPAREN, arr[j], linenum));}
		else if(arr[j] == ")"){tokens.push_back(Tok(::RPAREN, arr[j], linenum));}
		else if(arr[j] == ";"){tokens.push_back(Tok(::SC, arr[j], linenum));}
		else if(arr[j] == "print"){tokens.push_back(Tok(::PRINT, arr[j], linenum));}
		else if(arr[j] == "println"){tokens.push_back(Tok(::PRINTLN, arr[j], linenum));}
		else if(arr[j] == "Repeat"){tokens.push_back(Tok(::REPEAT, arr[j], linenum));}
		else if(arr[j] == "Begin"){tokens.push_back(Tok(::BEGIN, arr[j], linenum));}
		else if(arr[j] == "End"){tokens.push_back(Tok(::END, arr[j], linenum));}
		else if(arr[j] == "DONE"){tokens.push_back(Tok(::DONE, arr[j], linenum));}
		else if(regex_match(arr[j], regex("\\d+"))){tokens.push_back(Tok(::ICONST, arr[j], linenum));}
		else if(regex_match(arr[j], regex("\"([^\"]*)\""))){
			string s = arr[j]; // easier to type s
			string rstr = "";
			// check for escapes
			for(int k = 1; k < s.size()-1; k++){
				if(s[k] == '\\'){
					if(s[k+1] == 'n'){
						// newline
						rstr += "\n";
					}
					else{
						// treat it as the character after the backslash
						rstr += s[k+1];
					}
					k++;
				}
				else{
					// default
					rstr += s[k];
				}
			}
			// add the closing quotation mark
			//rstr += "\"";
			tokens.push_back(Tok(::SCONST, rstr, linenum));
		}
		else if(regex_match(arr[j], regex("[a-zA-Z][a-zA-Z0-9]*"))){tokens.push_back(Tok(::IDENT, arr[j], linenum));}
		else{tokens.push_back(Tok(::ERR, arr[j], linenum)); break;} // breaks after finding an error, so the rest will not be tokenized.
	}
	linenum++;
	return tokens;
}

vector<Tok> tokenize(string arg){
  int lineNumber = 1;
	ifstream fin2;
	// array of tokens
	vector<Tok> tokArr;

  // check if file can be opened
  fin2.open(arg);
  if(fin2.is_open() == false){
    cerr << "CANNOT OPEN " << arg << endl;
    return vector<Tok>();
  }
  // reading in file
  ifstream fin(arg);
  // array to get tokens from one line
  vector<Tok> arr;
  // loops through the lines
  while(fin.peek() != EOF){
    arr = getNextToken(fin, lineNumber);
    // adds the tokens from the new line to tokArr
		if(arr.size() > 0){
    	tokArr.insert(tokArr.end(), arr.begin(), arr.end());
		}
    // if an error was found, stop
    if(arr.size() > 0 && arr[arr.size()-1].GetToken() == ::ERR){
      break;
    }
    if(fin.peek() == EOF){
      tokArr.push_back(Tok(::DONE, "DONE", lineNumber));
      break;
    }
  }
	return tokArr;
}
// overriding the << operator
ostream& operator<<(ostream& out, const Tok& tok){
	out << numToToken[tok.GetToken()] << " " << tok.GetLexeme() << " " << tok.GetLinenum();
	return out;
}

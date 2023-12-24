/*
* Max Liu
* LexicalAnalyzer runner
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include "lex.h"
#include "LexicalAnalyzer.cpp"
using namespace std;

int main(int argc, char *argv[]){
	int lineNumber = 1;

	ifstream fin;

	// array of tokens
	vector<Tok> tokArr;

	// flags
	bool v = false;
	bool ids = false;
	bool iconsts = false;
	bool sconsts = false;

  for(int i = 1; i < argc; i++){
		string arg(argv[i]);
		if(arg == "-v"){v = true;}
		else if(arg == "-ids"){ids = true;}
		else if(arg == "-iconsts"){iconsts = true;}
		else if(arg == "-sconsts"){sconsts = true;}
		else if(arg[0] == '-'){cerr << "UNRECOGNIZED FLAG " << arg << endl; return 0;}
		else{
			// check if file can be opened
			fin.open(arg);
			if(fin.is_open() == false){
				cerr << "CANNOT OPEN " << arg << endl;
				return 0;
			}
			// reading in file
			ifstream fin(arg);
			// array to get tokens from one line
			vector<Tok> arr;
			// loops through the lines
			while(fin.peek() != EOF){
				arr = getNextToken(fin, lineNumber);
				// adds the tokens from the new line to tokArr
				tokArr.insert(tokArr.end(), arr.begin(), arr.end());
				// prints out the tokens and lexemes

				for(int i = 0; i < arr.size(); i++){
					cout << arr[i] << endl;
				}

				// if an error was found, stop
				if(arr[arr.size()-1].GetToken() == ::ERR){
					break;
				}
				if(fin.peek() == EOF){
					tokArr.push_back(Tok(::DONE, "DONE", lineNumber));
					break;
				}
			}
		}
	}
	// if the last argument is not a file
	// read in user input
	if(argv[argc-1][0] == '-' || argv[argc-1][0] == '.'){
		// array to get tokens from one line
		vector<Tok> arr;
		// loops until DONE
		bool isDone = false;
		while(!isDone){
			arr = getNextToken(cin, lineNumber);
			// adds the tokens from the new line to tokArr
			tokArr.insert(tokArr.end(), arr.begin(), arr.end());
			// prints out the tokens and lexemes

			for(int i = 0; i < arr.size(); i++){
				cout << arr[i] << endl;
			}

			// if an error was found, stop
			if(arr[arr.size()-1].GetToken() == ::ERR){
				break;
			}
			else if(arr[arr.size()-1].GetToken() == ::DONE){
				isDone = true;
			}
		}
	}
	if(tokArr[tokArr.size()-1].GetToken() != ::ERR){
		cout << "\nSummary:" << endl;
		cout << "Lines: " << lineNumber-1 << endl;
		cout << "Tokens: " << tokArr.size()-1 << endl;
	}
	// handles -v flag
	if(v){
		for(Tok x : tokArr){
			int num = x.GetToken();
			if(num == ::IDENT || num == ::ICONST || num == ::SCONST || num == ::ERR){
				cout << numToToken[num] << " (" << x.GetLexeme() << ") ";
			}
			else{
				cout << numToToken[num] << " ";
			}
		}
		cout << endl;
	}
	// handles -sconsts flag
	if(sconsts){
		vector<string> sconstArr;
		for(Tok x : tokArr){
			int num = x.GetToken();
			if(num == ::SCONST){sconstArr.push_back(x.GetLexeme());}
		}
		sort(sconstArr.begin(), sconstArr.end());
		for(string x : sconstArr){
			cout << x << endl;
		}
	}
	// handles -iconsts flag
	if(iconsts){
		vector<int> iconstArr;
		for(Tok x : tokArr){
			int num = x.GetToken();
			if(num == ::ICONST){iconstArr.push_back(stoi(x.GetLexeme()));}
		}
		sort(iconstArr.begin(), iconstArr.end());
		for(int x : iconstArr){
			cout << x << endl;
		}
	}
	// handles -ids flag
	if(ids){
		vector<string> idArr;
		for(Tok x : tokArr){
			int num = x.GetToken();
			if(num == ::IDENT){idArr.push_back(x.GetLexeme());}
		}
		sort(idArr.begin(), idArr.end());
		for(int i = 0; i < idArr.size(); i++){
			if(i != 0){
				if(idArr[i] != idArr[i-1]){
					cout << ", " + idArr[i];
				}
			}
			else{
				cout << idArr[i];
			}
		}
		cout << endl;
	}
}

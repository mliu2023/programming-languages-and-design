#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
    string str = "";
    string flag;
    bool flagWord = false;
    bool flagLine = false;

    // when there is only the file name and
    // no command line argument, displays the
    // missing flag message
    if (argc == 1) {
    	cout << "MISSING FLAG" << endl;
        return 0;
    }

    // when there is more than one command
    // line argument, displays the too many
    // flags message
    if (argc != 2) {
     	cout << "TOO MANY FLAGS" << endl;
        return 0;
    }

    // this recognizes the command line
    // argument and displays unknown flag
    // message when the command is unrecognized
    flag = argv[1];
    if (flag == "word") {
        flagWord = true;
    }
    else if (flag == "line") {
        flagLine = true;
    }
    else {
        cout << "UNKNOWN FLAG " << argv[1] << endl;
        return 0;
    }

    // gets the string from cin and executes the
    // appropriate command
    while(str != "bye") {
        getline(cin,str);
        string s = str;
        // if str does not end with some punctuation/symbol, add a blank space.
        char lastChar = s[s.length()-1];
        if(!regex_match(string(1, lastChar), regex("[ ;,\\(\\)\\.\\?\\!]"))){
          s += " ";
        }
        // using regex to tokenize the string.
        const regex r("(\\w+)([ ;\\?\\.\\!]+)(.*)");
        smatch m;
        vector<string> tokens;
        regex_search(s,m,r);
        tokens.push_back(m[1].str());
        // takes the first token, then tokenizes the rest of the string.
        while(regex_search(m[3].str(), m, r)){
          tokens.push_back(m[1].str());
        }
        // if flagWord, then print just the first token in the vector
        if (flagWord == true) {
          cout << tokens[0] << endl;
        }
        // if flagLine, print out the vector
        if (flagLine == true) {
          cout << "{";
          for(int i = 0; i < tokens.size(); i++){
            if(i != 0){
              cout << ", " + tokens[i];
            }
            else{
              cout << tokens[i];
            }
          }
          cout << "}" << endl;
        }
    }

    return 0;
}

/*
Please write functions so that if the user enters
a line, your program tokenize them into words separated
by space or other puncutations and create a vector of strings.

Requirement: Please use regular expressions!
*/
//Will Ackerman

#include <iostream>
#include <regex>
#include <string>
#include <cstring>


using namespace std;

vector<string> tokenize(string str)
{

//intialize std::vector<int> v;
  vector<string> tokens;

  //regex match ("(sub)(.*)");

//regex for the puncutations
regex match("[a-zA-Z]+");  //"[a-zA-Z]+"
//add end
regex_token_iterator<string::iterator> rend;
//iterator add
regex_token_iterator<string::iterator> t(str.begin(), str.end(), match);
//add to vector
while(t!=rend) { tokens.push_back(t->str()); t++;}
//return the std::vector<int> v;
  return tokens;
}

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
        getline(cin, str);
        if (str != "bye"){
          //cin >> str;
          if (flagWord == true) {
              cout << str << endl;
          }
          if (flagLine == true) {
            //call tokenize
              vector<string> t = tokenize(str);
              //print the vector
              for (int i = 0; i < t.size(); i++)
              {
                cout << t[i] << endl;
              }
          }

        }
    }

    return 0;
}

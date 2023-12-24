#include <iostream>
#include <regex>
#include <iterator>
using namespace std;

int main()
{
    //const regex r(" regex (my|your)(hello|hi)(.*)");
    const regex r("(\\w*)\\W(.*)");
    string myText = "int i = 0";
    char lastChar = myText[myText.length()-1];
    regex e("\\W");
    string s(1, lastChar);
    if(!regex_match(s,e)){
      myText += " ";
    }
    smatch m;
    regex_search(myText,m,r);
    //cout << m[0].str() << endl;
    cout << m[1].str() << endl;
    //cout << m[2].str() << endl;
    while(regex_search(m[2].str(), m, r)){
      //cout << m[0].str() << endl;
      cout << m[1].str() << endl;
      //cout << m[2].str() << endl;
    }
    cout << "-----" << endl;
    for (int i = 0; i < m.size(); i++) { // Alternatively. You can also do
       cout << m[i] << endl;
    }
    cout << endl;


    /*
    smatch m1;
    string yourText = "A piece of text that contains your regex.";
    bool yourTextContainsRegex = regex_search(yourText, m1, r);
    smatch::iterator ptr;
    cout << "The string matches are : ";
    for (ptr = m1.begin(); ptr < m1.end(); ptr++)
        cout << *ptr << " ";
    cout << endl;

    smatch m2;
    string theirText = "A piece of text that contains their regex.";
    bool theirTextContainsRegex = regex_search(theirText, m2, r);
    cout << "m2: ";
    cout << m2.size() << endl;


          cout << "the booleans: " << endl;
          cout    << myTextContainsRegex << '\n'
                  << yourTextContainsRegex << '\n'
                  << theirTextContainsRegex << '\n';
    */

}


//"(.*) (.*) (.*) (.*)"

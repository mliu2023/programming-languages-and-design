#include <iostream>
#include <regex>
#include <string>
using namespace std;
int main(){
  regex s("(?=.*\\d)(?=.*[a-z])(?=.*[A-Z])(?!.*\\s)(?=.*[!@#$*])");
  cout << regex_match("P^^FFXY%YK5U7K3*", s) << endl;
  cout << regex_match("o&54mqo5f2k4#^mx", s) << endl;
  cout << regex_match("h*m&aqwPVCf@^daJ", s) << endl;
  cout << regex_match("^%9T#c@2Y4YE9u9v", s) << endl;
  cout << regex_match("NM3bwmak7Ph5DEmH", s) << endl;
  cout << regex_match("fN!v@ApaeSFneS72", s) << endl;
}

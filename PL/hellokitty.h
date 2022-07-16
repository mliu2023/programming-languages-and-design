/*
* @author AT
*/
#include <iostream>
#include <string>
using namespace std;

class HelloKitty{
  int age;
  string name;

public:
  HelloKitty(){
    age = 0;
    name = "Kitty";
  }

  HelloKitty(int age, string name){
    this -> age = age;
    this -> name = name;
  }

  bool operator==(const HelloKitty hk) const
  { return (this -> age == hk.age) && (this -> name == hk.name); }

  bool operator!=(const HelloKitty hk) const
  { return (this -> age != hk.age) || (this -> name != hk.name); }

  // accessors
  int getAge() const{ return age; }
  string getName() const{ return name; }

  void print(){
    cout << name << " is " << age << " years old." << endl;
  }
};

extern ostream& operator<<(ostream& out, const HelloKitty& hk);

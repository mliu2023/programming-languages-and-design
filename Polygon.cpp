#include <iostream>
#include <string>
using namespace std;

class Polygon{
//public:
int numSides;
string name;

//private:
  //int x;
public:
  Polygon(){ this->numSides = 3; this->name = "Tri";}
  Polygon(int n, string na) { this->numSides = n; this->name = na;}
  ~Polygon(){}
  int getNumSides(){ return numSides;}
  string getName();
  bool operator==(const Polygon p) const
  { return this->numSides == p.numSides;}

};

//memeber method of a class
string Polygon::getName(){return name; }

int main(){
  Polygon p;
  Polygon p1(4, "Quad");
  Polygon p2;
  //cout << p << endl;
  cout << (p == p2) << endl;
  //cout << p.numSides << endl;
  //cout << p.x << endl;
  cout << p.getNumSides() << endl;
  cout << p.getName() << endl;
  cout << p2.getNumSides() << endl;
  cout << p2.getName() << endl;
}

#include<iostream>

using namespace std;

int main()

{

  cout<<"\n\nHello World,\nWelcome to my first C ++ program.\n\n"<<endl;

  int x = 1;
  cout << "x = " << x << endl;
  cout << "&x = " << &x << endl;

  int y;
  cout << "y = " << y << endl;
  cout << "&y = " << &y << endl;
  y = x;
  cout << "y = " << y << endl;

  int* z = &x;
  cout << "z = " << z << endl;
  cout << "*z = " << *z << endl;

}

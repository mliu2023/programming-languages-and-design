#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;



// true if there are an odd number of 1's in front, false if there are an even number of 1's in front
bool oddInFront(bool hatArr[], int pos){
  int counter = 0;
  for(int i = pos+1; i < 10; i++){
    if(hatArr[i] == 1){
      counter++;
    }
  }
  return counter % 2;
}
// i = 0 is the back, i = 9 is the front
int main(){
  // Get the system time.
   unsigned seed = time(0);

   // Seed the random number generator.
   srand(seed);

  string colorArr[2] = {"white", "black"};
  bool hatArr[10] = {0, 1, 1, 0, 1, 1, 1, 0, 0, 1};
  for(int i = 0; i < 10; i++)
    hatArr[i] = rand() % 2;
  for(int i = 0; i < 10; i++){
    cout << colorArr[hatArr[i]] << " ";
  }
  cout << endl;
  // prev is the state
  bool prev = oddInFront(hatArr, 0);
  cout << colorArr[prev] << endl;
  for(int i = 1; i < 10; i++){
    bool n = oddInFront(hatArr, i);
    // decision based on whether the observation is equal to the previous observation
    if(n != prev){
      cout << "black" << endl;
    }
    else{
      cout << "white" << endl;
    }
    prev = n;
  }
}

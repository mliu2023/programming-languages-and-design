// Max Liu
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// finds the sum of the digits of an integer recursively.
int sumDigits(int n){
  // if n is a digit, return n
  if(n/10 == 0){
    return n;
  }
  else{
    // last digit + sumDigits of the rest of the number.
    return n%10 + sumDigits(n/10);
  }
}
// takes in the array and the size.
// finds the sum of integers in an array.
int sumArr(int* arr, int size){
  int total = 0;
  for(int i = 0; i < size; i++){
    total += arr[i];
  }
  return total;
}
// takes in the vector and the size.
// finds the sum of integers in a vector.
int sumVector(vector<int> arr, int size){
  int total = 0;
  for(int i = 0; i < size; i++){
    total += arr[i];
  }
  return total;
}
// returns the reverse of the string.
// recursive function
string reverseString(string str){
  int size = str.size();
  // base case
  if(size == 0){
    return "";
  }
  // base case
  else if(size == 1){
    return str;
  }
  // puts the first character at the back and recursively calls.
  else{
    return reverseString(str.substr(1, size)) + str.front();
  }
}
// checks if the string is a palindrome or not.
// returns true if it is a palindrome, false otherwise.
bool isPalindrome(string str){
  int size = str.size();
  for(int i = 0; i < size/2; i++){
    if(str[i] != str[size-i-1]){
      return false;
    }
  }
  return true;
}
int main(){
    // sumDigits
    cout << sumDigits(59) << endl;
    cout << sumDigits(50) << endl;
    cout << sumDigits(200) << endl;
    // sumArr
    int* arr1 = new int[5];
    for(int i = 0; i < 5; i++){
        arr1[i] = i;
    }
    cout << sumArr(arr1, 5) << endl;
    // sumVector
    vector<int> arr2;
    arr2.push_back(1);
    arr2.push_back(2);
    arr2.push_back(9);
    cout << sumVector(arr2, 3) << endl;
    // reverseString
    string str1 = "289136";
    string str2 = "";
    cout << reverseString(str1) << endl;
    cout << reverseString(reverseString(str1)) << endl;
    cout << reverseString(str2) << endl;
    // isPalindrome
    string str3 = "28980";
    string str4 = "14641";
    cout << isPalindrome(str2) << endl;
    cout << isPalindrome(str3) << endl;
    cout << isPalindrome(str4) << endl;
    delete[] arr1;
}

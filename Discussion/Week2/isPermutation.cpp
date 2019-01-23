#include "set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

/*
  write a function that takes in two strings
  and returns a bool  
    true if the strings are equal to one another
     (have the same characters in any order)
    false if they are not

  except you can't use any string comparison functions
  you can only use the Set class that stores characters
*/
bool isPermutation(string a, string b)
{
	return false; // probably rarely does what you want it to
}


  // very limited testing
int main() {
	string s1, s2;

	  // same size, same characters
	s1 = "cersei";
	s2 = "cersei";
	assert(isPermutation(s1, s2) == (s1 == s2));

	  // different sizes
	s2 = "jaime";
	assert(isPermutation(s1, s2) == (s1 == s2));

	  // same size, different characters
	s1 = "tyrion";
	assert(isPermutation(s1, s2) == (s1 == s2));

	  // really similar
	s1 = "cercei";
	assert(isPermutation(s1, s2) == (s1 == s2));

	  // repeated letters, same string
	s1 = "sss";
	s2 = "sss";
	assert(isPermutation(s1, s2) == (s1 == s2));

	  // repeated letters, different string
	s2 = "ttt";
	assert(isPermutation(s1, s2) == (s1 == s2));

	cout << "Passed all tests!" << endl;
}

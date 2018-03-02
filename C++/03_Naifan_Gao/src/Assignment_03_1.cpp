//
//  Assignment_03_1.cpp
//
//  Created by Gabriel Taubin on 9/20/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 03_1" << endl;

  // A palindrome is a sequence of symbols that is the same when
  // reversed. For example the sentence, “A man a plan a canal
  // Panama”, has the same character sequence in the reverse order
  // (ignoring spaces and case). Write a program to reverse a string
  // constant and test if its sequence is equal to the forward
  // direction, as required by a palindrome.

  // 1) if argc<2 print usage message and quit
    if (argc < 2){
        cout << "usage" << endl;
        return 0;
    }

  // 2) use argv[1] as the input string.
    string sentence = argv[1];
    string temp = sentence;
    
  // 3) print "input string = " followed by the value of the input
  // string limited by quotes. For example, if the command line looks like
  //
  // $ assignment_03_1 hello_world
  //
  // your program output should look like this
  //
  // input string = "hello_world"
    cout << "input string = " << sentence << endl;
  // 4) measure the length of the input string and allocate an array
  // of the proper length to store the output string. Remember that
  // C-style strings must be terminated by a \0
    int len = sentence.length();
    cout << len << endl;
    char comparasion[len+1];
  // 5) perform the computations required to fill the output string
//    reverse(temp.begin(), temp.end());
//    temp.copy(comparasion, len);
    comparasion[len] = '\0';
    for(int i = 0; i< len; i++){
        comparasion[i] = sentence[len-i-1];
    }
  // 6) print "output string = " followed by the value of the output
  // string limited by quotes, as you had done for the input
  // string. Using the previous example, at this point your program
  // output should look like this
  //
  // input string = "hello_world"
  // outout string = "dlrow_olleh"
    cout << "output string = " << comparasion << endl;
  // 7) indicate whether or not input string is palindrome or not
  if(sentence.compare(string(comparasion))==0/* replace by proper condition */)
    cout << "input string is palindrome" << endl;
  else
    cout << "input string is NOT palindrome" << endl;

  // 8) Delete any memory allocated in your program using the new()
  // operator

  return 0;
}

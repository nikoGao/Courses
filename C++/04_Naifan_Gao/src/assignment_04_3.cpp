//
//  Assignment_04_3.cpp
//
//  Created by Gabriel Taubin on 9/25/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <string.h>
#include "myStringFunctions.hpp"
using namespace std;

/////////////////////////////////////////////////////////

// Write a set of functions for processing strings. The strings are
// represented as an array of char data types with a terminating 0 or
// null character. The functions to be implemented are:

// A) concatenate two strings – inputs are two strings, the output is
// a single string with the input strings joined in a single
// null-terminated array. Note, there should only be one null
// termination on the output. The function name should be concat.

// B) find a substring – inputs are two strings, s and k. The function
// should determine if k is a proper substring of s. That is, it is
// possible that s and k are the same string, but k can never be
// longer than s. The outputs should be a bool return indicating true
// if k is a substring of s. Also the array index location of the
// start of k in s should be output as a reference to an unsigned
// value. The function name should be substr.

// C) reverse a string in place – this function has a single input and
// no return value. The input is a string, the result of function
// execution is that the input string is reversed in order. The
// function name should be reverse.

// Declare these functions in a separate myStringFunctions.hpp file,
// implement them in a separate myStringFunctions.cpp file. Save the
// two files in the src directory for this assignment. Edit the
// CMakeLists.txt file so that your functions are compiled and linked
// with your assignment_04_3 program. Remember to include your new
// header file in the file that contains your main() program.

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 04_3" << endl;
//    string str = "Hello";
//    reverse(str);
//    cout << str << endl;
//    unsigned cur = 0;
//    bool result = substr("abcdefg", "fgh", cur);
//    cout << result << endl;
//    cout << cur << endl;

  // Call your program as follows
    //switch...case has to be used with integer, if want to use it, maybe should need HashMap to allocate function with num;
    string function = argv[1];
    int function_number = function=="-c"?0:(function=="-s"?1:(function=="-r"?2:3));
    switch (function_number) {
        case 0:
        {
            if(argc < 4){
                cout << "Input arguments' number is wrong." << endl;
                return 0;
            }
            const char * str1 = argv[2];
            const char * str2 = argv[3];
            char * concat_str = concat(str1, str2);
            printf("concat(\"%s\", \"%s\") = \"%s\" \n",str1, str2, concat_str);
            delete[] concat_str;
            break;
        }
        case 1:
        {
            if(argc < 4){
                cout << "Input arguments' number is wrong." << endl;
                return 0;
            }
            const char * str1 = argv[2];
            const char * substring = argv[3];
            unsigned index = 0;
            bool find = substr(str1, substring, index);
            if (find){
                printf("substr(\"%s\", \"%s\") = true (%d) \n", str1, substring, index);
            }else{
                printf("substr(\"%s\", \"%s\") = false \n", str1, substring);
            }
            break;
        }
        case 2:
        {
            if(argc < 3){
                cout << "Input arguments' number is wrong." << endl;
                break;
            }
            string string1 = argv[2];
            string temp = string1;
            reverse(string1);
            cout << "reverse( \"" << temp << "\") = \"" << string1 << "\"" << endl;
            break;
        }
        default:
            cout << "Input cmd argument is wrong." << endl;
            break;
    }
    
  // assignment_04_3 cmd str1 [str2]

  // The first cmd argument should be equal to one of the following
  // strings “-c”, “-s”, or “-r”; otherwise print a usage message and
  // quit. The number of required additional arguments depends on the
  // value of the cmd argument.

  // If the cmd argument is equal to “-c”, two additional arguments are
  // required. If the number of arguments is incorrect, print the usage
  // message and quit. Run your concat function using the two additional
  // command line arguments as input. Print the result using the
  // following format

  // concat(str1,str2) = result

  // where the strings str1, str2, and result should be printed between
  // double quotes, as in this example

  // concat(“Hello ”,”World”) = “Hello World”

  // Note that there is a space at the end of the first string. To
  // specify strings with white spaces in the command line you need to
  // use single or double quotes as well. In this example, you would
  // call your program as follows

  // assignment_04_3 –c “Hello “ World


  // If the cmd argument is equal to “-s”, two additional arguments
  // are required. If the number of arguments is incorrect, print the
  // usage message and quit. Run your substr function using the two
  // additional command line arguments as input. If the value returned
  // by your function is false, print the result using the following
  // format

  // substr(str1,str2) = false

  // where the strings str1, and str2 should be printed between double
  // quotes. If the value returned by your function is truea, print
  // the result using the following format

  // substr(str1,str2) = true (index)

  // where the strings str1, and str2 should be printed between double
  // quotes, and index is the index into str1 (regarded as an array)
  // where the substring str2 starts, returned by your function.

  // If the cmd argument is equal to “-r”, only one additional argument
  // are required. If the number of arguments is incorrect, print the
  // usage message and quit. Run your reverse function using the
  // additional command line arguments a input. Print the result using
  // the following format

  // reverse(str1) = result

  // where the stringS str1, and result should be printed between double quotes.

  // Note also that C libraries exist to achieve these functions. Do not
  // use them in your implementation. Also use const qualifiers where
  // appropriate.

  return 0;
}

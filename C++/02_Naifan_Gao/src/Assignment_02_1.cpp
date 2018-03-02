//
//  Assignment_02_1.cpp
//
//  Created by Gabriel Taubin on 9/18/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <math.h>

using namespace std;
#define PI 3.14159265

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 02_1" << endl;

  // Newton's method:
  // Write a program to find a solution of the equation

  // cos⁡(x)=0

//   using 32 bits real types (i.e. float). Devise a termination
//   condition that insures that the solution will be accurate to the
//   precision of the computation. Observe what happens if you ask for
//   a more precise solution, by insisting that f(x_n )=0 exactly, as
//   the termination condition.

  // first make it work with a hardcoded value
  // float x_initial = -1.5; // should converge to -\pi/2
    if (argc < 2){
        cout << "Please input at least one argument" << endl;
        return 0;
    }
    float x_initial = atof(argv[1]); // should converge to \pi/2
//    float x_initial = 1.5;
  // once it works properly for harcoded values, read initial value
  // from the command line
  //
  // print a "usage" message if argc<2
//   float x_initial = 1.5;

  cout << "x_initial = " << x_initial << endl;

  unsigned n_iter   = 0;
  unsigned n_digits = 0; // number of correct digits
  float x_final  = x_initial;
  float error = 0.5e-7;   //as float precison is 7-digit

  // (do your work here) ...
  float function = cos(x_final);
  while(abs(function) > error){
      function = cos(x_final);
      ++n_iter;
      float temp = function/sin(x_final);
      x_final += temp;
  }
//    float threshold = 0.00005;
    string result = to_string(x_final);
    int pos = result.find(".");
    n_digits = result.length() - pos;
    cout.precision(8);
  cout << "x_final  = " << x_final << endl;
  cout << "n_iter   = " << n_iter << endl;
  cout << "n_digits = " << n_digits << endl;
    
  return 0;
}

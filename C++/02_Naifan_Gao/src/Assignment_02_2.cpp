//
//  Assignment_02_2.cpp
//
//  Created by Gabriel Taubin on 9/18/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <iomanip>
#define PI 3.14159265358979323
using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 02_2" << endl;

  // Consider the following iterative scheme, which can be used to compute $\pi$ as 
  //
  // $\pi = lim_{n\rightarrow\infty}⁡ a_n = lim_{n\rightarrow\infty}⁡ b_n$
  //
  // described in detail in http://www.cs.umb.edu/~offner/files/pi.pdf
  //
  // where
  // a_0 = 2*sqrt(3);
  // b_0 = 3; 
  //
  // $ a_{k+1}={2*a_k*b_k}/{a_k+b_k} $
  // and
  // $ b_{k+1}=\sqrt(a_{k+1}* b_k} $
  //
  // Implement this method using a while loop and then using a for
  // loop. 
//    if (argc < 2){
//        cout << "Not enough argument" << endl;
//        return 0;
//    }
  unsigned specified_max_n_digits = 17;

  cout << "specified_max_n_digits = " << specified_max_n_digits << endl;

  // Determine a stopping condition that computes \pi to the specified
  // number of digits, or to the the maximum number of digits that are
  // representable in a real number of the given type (float and
  // double), if the specified number of digits is larger than the
  // maximum number or negative;
    
    unsigned computed_n_digits_float = 0;
    float    pi_float = 0.0f;
    long computed = 0;

  // implement the float version here
    float a = 2*sqrt(3), b = 3.0;
    if (specified_max_n_digits > 7 || specified_max_n_digits <= 0){
        computed_n_digits_float = 7;
    }else{
        computed_n_digits_float = specified_max_n_digits;
    }
    long termination = PI * pow(10, computed_n_digits_float);
    while(termination-computed > 1){
        a = 2*a*b/(a+b);
        b = sqrt(a*b);
        computed = (long)(b*pow(10, computed_n_digits_float));
    }
    pi_float = computed/pow(10, computed_n_digits_float);
    cout.precision(computed_n_digits_float+1);
  cout << "pi_float = " << pi_float << endl;
  cout << "computed_n_digits_float = " << computed_n_digits_float << endl;

  unsigned computed_n_digits_double = 0;
  double   pi_double = 0.0;
    long computed_2 = 0;
    double a_2 = 2*sqrt(3), b_2 = 3.0;
  // implement the double version here
    if (specified_max_n_digits > 16 || specified_max_n_digits <= 0){
        computed_n_digits_double = 16;
    }else{
        computed_n_digits_double = specified_max_n_digits;
    }
    termination = PI * pow(10, computed_n_digits_double);
    for(int i = 0; i< 100; i++){
        a_2 = 2*a_2*b_2/(a_2+b_2);
        b_2 = sqrt(a_2*b_2);
        computed_2 = (long)(b_2*pow(10, specified_max_n_digits));
        if (computed_2 == termination){
            break;
        }
    }
    pi_double = computed_2/ pow(10, computed_n_digits_double);
    cout.precision(computed_n_digits_double+1);
  cout << "pi_double = " << pi_double << endl;
  cout << "computed_n_digits_double = " << computed_n_digits_double << endl;

    
  return 0;
}

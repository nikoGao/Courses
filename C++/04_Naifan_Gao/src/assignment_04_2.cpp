//
//  Assignment_04_2.cpp
//
//  Created by Gabriel Taubin on 9/25/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;
const double gold_ratio = (1 + sqrt(5))/2;

/////////////////////////////////////////////////////////

// Add a first function above your main program to compute Fibonacci
// numbers using recursive functions. Use unsigned long as the input
// and output data types. The first two Fibonacci numbers are f_0=0
// and f_1=1. The remaining Fibonacci numbers are the sum of the
// previous two numbers. Thus the sequence (f_n)_{n>=0} is:
//
// 0, 1, 1, 2, 3, 5, 8, 13 … 
//
// It is well known that the limit of the ratio of successive
// Fibonacci numbers as the n approaches infinity is the golden ratio

// lim_{n\rightarrow\infty} \frac{f_{n+1}}{f_{n}} = (1+\sqrt{5})/2

// The golden ratio has many applications in the arts.  For example,
// it is the ideal ratio of the height to the width of a doorway in
// order to be aesthetically pleasing.

// Write a second function named goldenRatio, with two parameters,
// precision (input), and firstIndex (output), that calls your
// original function to approximate the golden ratio, as a function of
// the successive values of the Fibonacci sequence. The first
// parameter specifies the desired number of correct digits in the
// output value. The second parameter should be used to return the
// first index in the Fibonacci sequence for which the approximation
// has the desired number of correct digits.  You can use the fact
// that you know the limit value in your implementation of this
// function.

// Use double as the return data type. Use unsigned as the data type
// for the two parameters. Keep in mind that the second parameter will
// be used to return the value determined in the function.
unsigned long Fibonacci(unsigned long N){
     if (N > 1){
        return Fibonacci(N-1)+Fibonacci(N-2);
    }else if(N == 1){
        return Fibonacci(0)+1;
    }else{
        return 0;
    }
}

double goldRatio(unsigned precision, unsigned& firstIndex){
//    unsigned long criterion = 0;
//    double temp_ratio = gold_ratio;
//    while(precision > 0){
//        criterion += (unsigned long)floor(temp_ratio);
//        temp_ratio *= 10;
//        precision--;
//    }
    double ep1 = gold_ratio, ep2, result;
    ep2 = pow(10.0 ,-(double)(precision));
    result = (double)Fibonacci(firstIndex+1)/(double)Fibonacci(firstIndex);
    while(fabs(ep1-result)> ep2/2){
        firstIndex++;
        result = (double)Fibonacci(firstIndex+1)/(double)Fibonacci(firstIndex);
    }
    return result;
}

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 04_2" << endl;
    if (argc < 3){
        cout << "Error argument number" << endl;
        return 0;
    }else{
        if (string(argv[1])=="-f"){
            unsigned long N = atoi(argv[2]);
            if ((N==0 && argv[2]!=string("0"))|| N == LONG_MAX){
                return 0;
            }
            for(unsigned long i = 0; i <= N; i++){
                cout << right;
                switch (i%5) {
                    case 0:
                        cout << setw(9)  << ' '<< Fibonacci(i) << ' ';
                        break;
                    case 4:
                        cout << Fibonacci(i) << endl;
                        break;
                    default:
                        cout << Fibonacci(i) << ' ';
                        break;
                }
            }
            cout << endl;
        }else if (string(argv[1])=="-g"){
            unsigned precision = atoi(argv[2]);
            if ((precision==0 && argv[2]!=string("0"))|| precision == INT_MAX){
                return 0;
            }else if(precision >= 16){
                cout << "Precision must be smaller than 16." << endl;
                return 0;
            }
            unsigned iteration = 1;
            double result = goldRatio(precision, iteration);
            cout.precision(16);
            cout << "goldenRatio(" << precision << ") = " << result << "{ firstIndex=" << iteration << " }" << endl;
        }else{
            cout << "Input Function is wrong" << endl;
            return 0;
        }
    }
  // Call your program with two arguments
  //
  // assignment_04_02 cmd N
  //
  // If the number of arguments is incorrect, print a usage message
  // and quit.
  //
  // If the cmd argument is equal to the string "-f":
  //
  // 1) Read an unsigned value N from the next argument.  If the
  // conversion of the argument to unsigned fails, print a usage
  // message and quit.
  //
  // 2) Print all the Fibonacci numbers (f_n), 0<=n<=N, as a table
  // with five numbers per row. The five columns should have exactly
  // 15 spaces.  Leave one space of separation between columns, and
  // align all the numbers on the right hand side.

  // If the cmd argument is equal to the string "-g"
  //
  // 1) Read an unsigned value N from the next argument.  If the
  // conversion of the argument to unsigned fails, print a usage
  // message and quit.
  //
  // 2) Determine the minimum number of iterations that produces the
  // golden ratio to a floating point precision of N digits.  Print
  // using the following format
  //
  // goldenRatio(N) = <value returned by your function> { firstIndex }
  //
  // If the cmd argument does not match any of the previous two
  // strings, print a usage message and quit.
    
  return 0;
}

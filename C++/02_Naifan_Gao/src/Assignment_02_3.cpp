//
//  Assignment_02_3.cpp
//
//  Created by Gabriel Taubin on 9/18/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <math.h>
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 02_3" << endl;

  // Show that the following code segment

  // the input value is x
  double x=.5;
  // number of iterations
  int n = 100;

  int k = 0;
  double fact_k = 1.0;
  double x_k = 1.0;
  double exp_x_1 = 1.0; // output value approximates exp(x)
  while(++k<=n) {
    x_k *= x;
    fact_k *= k;
    exp_x_1 += x_k/fact_k;

    // add print statement here
  }
    double real_value = exp(0.5);
    cout.precision(17);
    cout << "final value = " << exp_x_1 << endl;
    cout << "real value = " << real_value << endl;
    cout << "relative error = " << abs(exp_x_1 - real_value) * 100 << "%" << endl;
  // print final value, real value, and relative error as a percentage
  
  // approximates the value of $e^x$ based on the power series expansion
  //
  // e^x = \sum_{k=0}^{\infty} \frac{x^k}{k!}
  //     = \lim_{n\rightarrow\infty} \sum_{k=0}^{n} \frac{x^k}{k!} = 
  //

  // Implement a program that reads the values of x and n from the
  // command line and print out the result of the computation. You can
  // use the library functions
    
  // double atof (const char* str);
  // int atoi (const char * str);

  // defined in the system header file stdlib.h to parse the command
  // line strings. Print a "usage" message if the number of command
  // line arguments is not sufficient, and quit.

  // Add a print statement within the loop to report the
  // current approximation and the error between the current
  // approximation and the correct value for each value of the
  // variable i. Use the library function

  // double exp(double x);

  // defined in the system header file math.h to compute the correct
  // value. 
    cout << "--------------------" << "Question B" << "------------------------" << endl;
    if(argc < 3){
        cout << "Must have at least one argument" << endl;
        return 0;
    }
    double coff_x = atof(argv[1]);
    int  coff_loop = atof(argv[2]);
    int m = 1;
    double cal_result_1 = 1.0;
    double cal_result_2 = 1.0;
    double x_m = 1.0;
    double appro_result = exp(coff_x);
    cout << "exp(" << x << ") = " << appro_result << endl;
    double err1 = 0.0;
    double err2 = 0.0;
    double fact_loop = 1.0;
    int times1 = 0, times2 = 0;
    while (m <= coff_loop){
        x_m *= x;
        fact_loop *= m;
        cal_result_1 += x_m/fact_loop;
        err1 = abs(cal_result_1-appro_result) * 100;
        cout << "error between the current approximation of e^x and the correct value is: " << err1 << "%" << endl;
        cout << "--------------------" << "Question C" << "------------------------" << endl;
        cal_result_2 = pow((1+x/m), (double)m);
        err2 = abs(cal_result_2-appro_result) * 100;
        cout << "current approximation of power series is: " << cal_result_1 << ", current approximation of identity is " << cal_result_2 << endl;
        if (cal_result_1 == appro_result && times1 == 0){
            times1 = m;
        }
        if (cal_result_2 == appro_result && times2 == 0){
            times2 = m;
        }
        m++;
    }
    if (times1 > times2){
        cout << "(1+x/n)^n function converge faster" << endl;
    }else{
        cout << "power series expansion converge faster" << endl;
    }
    
  

  // In the same loop, add statements to approximate the value of e^x
  // based the following identity

  // e^x = \lim_{n\rightarrow\infty} \left(1+\frac{x}{n}\right)^n

  // Modify the print statements to report the two approximations on the same line. 

  // Which of the two approximations converge faster? Which one of the
  // two methods has lower complexity?
    
    return 0;
}

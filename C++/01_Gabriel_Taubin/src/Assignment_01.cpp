//
//  Created by Gabriel Taubin on 9/13/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 1" << endl;
    double x = 0.14580858;
    float y = 0.5463275f;
    cout.precision(5);
    cout << x << endl;   //should print out 0.14581;
    cout << y << endl;   //should print out 0.54633;
    


  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 2" << endl;
    unsigned short num1, num2;
    int num3 = 8;
    long num4 = 94290L;
    num1 = num3/2;
    num2 = num4*100000000000;
    cout << num1 <<endl;
    cout << num2 << endl;
    
  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 3" << endl;
    string ss = "0x3f400000";
    

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 4" << endl;
    cout << "Question A" <<endl;
    float num10 = 10.0F;
    int num11 = 10;
    bool float_equal_int = (num10==num11);
    cout << float_equal_int << endl;

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 5" << endl;

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 6" << endl;
    double yd = 1.0, xzero = 1.0e-200;
    double inf =yd/(xzero*xzero);
    cout << inf << endl;
    cout << 0*inf << endl;
    cout << (0*inf==inf) << endl;

    
    return 0;
}

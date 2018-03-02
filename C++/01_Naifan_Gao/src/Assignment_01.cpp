//
//  Created by Gabriel Taubin on 9/13/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

union ulf{
    unsigned long ul;
    float f;
};

int main(int argc, const char * argv[]) {

    cout << "------------------------------------------------------------" << endl;
    cout << "Problem 1" << endl;
    double x = 0.14580858946574839;
    float y = 0.54632754f;
    cout.precision(1);
    cout << x << endl;
    cout << y << endl;
    cout.precision(2);
    cout << x << endl;
    cout << y << endl;
    cout.precision(3);
    cout << x << endl;
    cout << y << endl;
    cout.precision(4);
    cout << x << endl;
    cout << y << endl;
    cout.precision(5);
    cout << x << endl;
    cout << y << endl;
    cout.precision(6);
    cout << x << endl;
    cout << y << endl;
    cout.precision(7);
    cout << x << endl;
    cout << y << endl;
    cout.precision(8); //precision > float.length, start to go wrong, precision 7
    cout << x << endl;
    cout << y << endl;
    cout.precision(9);
    cout << x << endl;
    cout << y << endl;
    cout.precision(10);
    cout << x << endl;
    cout << y << endl;
    cout.precision(17); //precision > double.length, keep as its real length, double 16
    cout << x << endl;
    cout << y << endl;
    
    
    cout << "------------------------------------------------------------" << endl;
    cout << "Problem 2" << endl;
    unsigned short num1, num2;
    unsigned int num3, num4;
    unsigned long num5, num6;
    unsigned char num13, num14;
    cout << "signed int -> unsigned short" <<endl;
    int num7 = 2147483647, num8 = -2147483648;
    num1 = num7;
    num2 = num8;
    cout << num1 <<endl;
    cout << num2 <<endl;
    cout << "signed long -> unsigned short" <<endl;
    long num9 = 2147483647, num10 = -2147483648;
    num1 = num9;
    num2 = num10;
    cout << num1 << endl;
    cout << num2 << endl;
    cout << "signed short -> unsigned short" << endl;
    short num11 = 32767, num12 = -32768;
    num1 = num11, num2 = num12;
    cout << num1 <<endl;
    cout << num2 << endl;
    cout << "signed char -> unsigned short" <<endl;
    char num15 = 127, num16 = -128;
    num1 = num15, num2 = num16;
    cout << num1 <<endl;
    cout << num2 << endl;
    cout << "signed short -> unsigned int" << endl;
    num3 = num11;
    num4 = num12;
    cout << num3 << endl;
    cout << num4 << endl;
    cout << "signed int -> unsigned int" << endl;
    num3 = num7;
    num4 = num8;
    cout << num3 << endl;
    cout << num4 << endl;
    cout << "signed long -> unsigned int" << endl;
    num3 = num9;
    num4 = num10;
    cout << num3 << endl;
    cout << num4 << endl;
    cout << "signed char -> unsigned int" << endl;
    num3 = num15, num4 = num16;
    cout << num4 << endl << num4 <<endl;
    cout << "signed short -> unsigned long" << endl;
    num5 = num11;
    num6 = num12;
    cout << num5 << endl;
    cout << num6 << endl;
    cout << "signed int -> unsigned long" << endl;
    num5 = num7;
    num6 = num8;
    cout << num5 << endl;
    cout << num6 << endl;
    cout << "signed long -> unsigned long" << endl;
    num5 = num9;
    num6 = num10;
    cout << num5 << endl;
    cout << num6 << endl;
    cout << "signed char -> unsigned long" << endl;
    num5 = num15, num6 = num16;
    cout << num5 << endl << num6 << endl;
    cout << "signed char -> unsigned char" << endl;
    num13 = num15, num14 = num16;
    cout << num13 << endl << num14 << endl;
    cout << "signed short -> unsigned char" << endl;
    num13 = num11, num14 = num12;
    cout << num13 << endl << num14 << endl;
    cout << "signed int -> unsigned char" << endl;
    num13 = num7, num14 = num8;
    cout << num13 << endl << num14 << endl;
    cout << "signed long -> unsigned char" << endl;
    num13 = num9, num14 = num10;
    cout << num13 << endl << num14 << endl;
    
    cout << "------------------------------------------------------------" << endl;
    cout << "Problem 3" << endl;
    ulf u;
    string str = "3F400000";
    stringstream ss(str);
    ss >> hex >> u.ul;
    float f = u.f;
    cout << f << endl;
    
    
    
    cout << "------------------------------------------------------------" << endl;
    cout << "Problem 4" << endl;
    cout << "Question A" <<endl;
    float float_num = 10.01543F;
    double double_num = 10.0574839208432980982979462;
    int int_num = 10;
    bool float_equal_int = (float_num==int_num);
    cout << "float compare with int" << endl;
    cout << float_equal_int << endl;
    cout << "double compare with int" << endl; 
    cout << (double_num == int_num) << endl;
    
    
    
    cout << "------------------------------------------------------------" << endl;
    cout << "Problem 5" << endl;
    double yd = 1.0, xzero = 1.0e-200;
    double inf =yd/(xzero*xzero);
    cout << inf << endl;
    cout << 0*inf << endl;
    cout << (0*inf==inf) << endl;


    
    return 0;
}

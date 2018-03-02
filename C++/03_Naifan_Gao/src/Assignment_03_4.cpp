//
//  Assignment_03_4.cpp
//
//  Created by Gabriel Taubin on 9/20/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 03_4" << endl;

  // Determine if your computer CPU is big-endian or little-endian by
  // implementing a computation that will reveal the byte order of the
  // representation of numerical data types. Verify your conclusion by
  // using your debugger to examine the contents of memory locations
  // holding a known unsigned short integer.

  // 1) if(argc<2) print usage message
    if (argc<2){
        cout << "You must provide at least one argument" << endl;
        return 0;
    }

  // 2) read the unsigned short value from argv[1] 
  unsigned short value_s = atoi(argv[1]);
//    unsigned short value_s = 1000;

  // 3) print value_s in base 10
  cout << "value_s(10) = " << value_s << endl;

  // 4) print value_s in hexadecimal format with 4 significant digits;
  // make sure that the printed values start with 0x. For example, if
  // value_s==1, your program should print 0x0001
  cout << "value_s(16) = " << "0x" << setfill('0') << setw(4)<< hex << value_s/* how do you print value_s in hex ???*/ << endl;

  // 5) determine the first and second bytes of value_s
  unsigned char value_c_0 = value_s&0xff;
  unsigned char value_c_1 = (value_s>>8)&0xff;

  // 6) print the two values in hexadecimal format with 2 significant digits;
  // make sure that the printed values start with 0x

  cout << "value_c_0 = " << "0x" << setfill('0') << setw(2) << hex << (int)value_c_0 /* how ??? */ << endl;
  cout << "value_c_1 = " << "0x" << setfill('0') << setw(2) << hex << (int)value_c_1 /* how ??? */ << endl;

  // 7) determine the endiannes and print a statement
    unsigned char byte[2];
    for(int i = 0; i < sizeof(value_s); ++i){   
        byte[i] = *((unsigned char *)&value_s + i);
    }
  if(byte[0]== value_c_1 && byte[1] == value_c_0)
    cout << "big-endian" << endl;
  else
    cout << "little-endian" << endl;
    
  return 0;
}

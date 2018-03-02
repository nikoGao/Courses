//
//  Assignment_04_1.cpp
//
//  Created by Gabriel Taubin on 9/25/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <typeinfo>
#include <stdio.h>
using namespace std;

/////////////////////////////////////////////////////////

// Write a function that returns the translation vector between two
// 2-dimensional positions. Represent the positions as double
// variables and the result as a pair of double values. Pass both
// inputs and outputs as arguments to the function. Use references as
// argument types. Use the const qualifier where appropriate. Return a
// bool result that is false if the input points are the same.
bool Translation(const double (&point)[4], double (& tv)[2]){
    double x1 = point[0];
    double y1 = point[1];
    double x2 = point[2];
    double y2 = point[3];
    if (x1==x2 && y1==y2){
        return false;
    }else{
        tv[0] = x2-x1;
        tv[1] = y2-y1;
        return true;
    }
}

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 04_1" << endl;


  // Call the function that you wrote from your main program for the
  // pair-wise distances. Read the coordinates of the two points from
  // the command line as follows

  // assignment_01_1 x1 y1 x2 y2
    double arr[4];
    double tvec[2];
    
    
    if (argc != 5){
        cout << "The number of input arguments is incorrect" << endl;
        return 0;
    }else{
        int i = 1;
        while(i<5){
            //how to determine your input is just not 0.0?
            double temp = atof(argv[i]);
            if(temp==0 && *argv[i] != 48){
                cout << "Input arguments type error" << endl;
                return 0;
            }else{
                arr[i-1] = temp;
                i++;
            }
        }
        bool result = Translation(arr, tvec);
        if(result){
            printf("p1 = (%f, %f) ", arr[0], arr[1]);
            printf( "p2 = (%f, %f) ",arr[2], arr[3]);
            printf( "tvec = (%f, %f) \n", tvec[0], tvec[1]);
        }else{
            printf("These two points are same.\n");
        }
    }
//    cout << result << endl;
//    cout << tvec[0] << endl;
//    cout << tvec[1] << endl;
  // Write a usage message if the number of arguments is not correct,
  // and if the conversion of any of the arguments to double fails.

  // Print the result using the following format

  // p1=(x1,y1) p2=(x2,y2) tvec=(tx,ty)

  // Use the following points to test your program:

  // p1 = (5.31, 7.41), p2 = (413.13, 84.154),
  // p1 = (8.815, 20.7114), p2 = (5.31, 7.41).

  return 0;
}

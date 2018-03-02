//
//  Assignment_03_5.cpp
//
//  Created by Gabriel Taubin on 9/20/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 03_5" << endl;

  // 1) if (argc<2) print usage message
    if (argc<2){
        cout << "No argument is provided" << endl;
        return 0;
    }
//   Following are the first few prime numbers: 2, 3, 5, 7, 11, 13,
//   17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
//   83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
//   151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199.

  // 1) Store these numbers in a one- dimensional array. 
    int array[46] = {2, 3, 5, 7, 11, 13,
        17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
        83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149,
        151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};
  // 2) read a query value from argv[1]
    double target = atof(argv[1]);
  // 3) Write a program to find the nearest prime number to the given
  // query value by carrying out binary search.
 
  // Binary search operates on a sorted list of numbers. A query
  // number is compared with the middle number of the range of stored
  // values. If the query is less than the middle number, the new
  // upper bound on the range is the next stored number below the
  // middle. If the query is greater than the middle number then the
  // lower bound on the range is the next stored number above the
  // middle. If the query equals the middle number then the answer is
  // found. A more complete description of binary search is given at

  // http://en.wikipedia.org/wiki/Binary_search

  // Consider in your program issues such as the case where the query
  // is outside the range of the stored numbers. Test your program
  // using all the even numbers from 2 to, and including, 200.
  
  // 4) if the query value is lower than the first element of the
  // array, report according to this format
  // -1.35 < [value of first element of the array]

  // 5) if the query value is equal to one element of the array,
  // report according to this format
  //
  // 5 is the 3-rd element of the array
  //
  // make sure that you report 1-st, 2-nd, 3-rd, 4-th, etc correctly

  // 6) if the query value is between two elements of the array,
  // report according to this format
  // 5 < 5.35 < 7

  // 7) if the query value is larger than the last element of the
  // array, report according to this format
  // -1.35 > [value of last element of the array]
    int start = 0;
    int end = 45;
    int mid = 0;
    if(array[start]>target){
        cout << target << '<' << array[start] << endl;
    }else if(target > array[end]){
        cout << target << '>' << array[end] << endl;
    }else{
        while(start < end){
            mid = (end - start)/2 + start;
            if (array[mid] == target){
                int remainder = mid % 10;
                if (remainder==0 && (mid != 10)){
                    cout << target << " is the " << mid+1 << "-st element of the array" << endl;
                }else if (remainder == 1 && mid != 11){
                    cout << target << " is the " << mid+1 << "-nd element of the array" << endl;
                }else if (remainder == 2 && mid != 12){
                    cout << target << " is the " << mid+1 << "-rd element of the array" << endl;
                }else{
                    cout << target << " is the " << mid+1 << "-th element of the array" << endl;
                }
                break;
            }else if (array[mid] > target){
                end = mid - 1;
            }else{
                start = mid + 1;
            }
        }
        if(end-start == 1 && array[start] < target && array[end] > target){
            cout << array[start] << '<' << target << '<' << array[end] << endl;
        }else if(end-start == 1 && array[start] > target && array[start-1] < target){
            cout << array[start-1] << '<' << target << '<' << array[start] << endl;
        }
        if (start==end && array[start] > target){
            cout << array[start-1] << '<' << target << '<' << array[start] << endl;
        }else if (start==end && array[start] < target){
            cout << array[start] << '<' << target << '<' << array[start+1] << endl;
        }
        if (array[start] == target && start == end){
            if (start == 0){
                cout << target << " is the " << start+1 << "-st element of the array" << endl;
            }else{
                cout << target << " is the " << start+1 << "-th element of the array" << endl;
            }
        }
    }
  return 0;
}

//
//  Assignment_03_3.cpp
//
//  Created by Gabriel Taubin on 9/20/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <math.h>
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Naifan Gao" << endl; // print your name
  cout << "Problem 03_3" << endl;

  // 1) Print a usage message if argc<2 and quit
    if (argc<2){
        cout << "You must provide at least one argument" << endl;
        return 0;
    }
  // 2) read the number n from argv[1].
  int n = 0;
    n = atoi(argv[1]) + 1;
  // 3) Design a way to store Pascal’s triangle on the stack (local scope
  // declaration) using a linear array. Note that the first row
  // requires one memory location, the second row requires two, the
  // third row requires three, and so on. Your memory representation
  // should be able to store any lower triangular matrix without
  // wasting storage. Given a pair (n,k) , where n≥k≥0, you need to
  // derive a formula to compute the location in the linear array
  // where the corresponding binomial coefficient is stored. A square
  // array is not the solution to this problem.
    int** lines = new int*[n];
    for(int r = 0; r<n; r++){
        lines[r] = new int[r+1];
        if(r==0){
            lines[0][0] = 1;
        }else if(r==1){
            lines[r][0] = 1;
            lines[r][1] = 1;
        }else{
            lines[r][0] = 1;
            lines[r][r] = 1;
            for(int j = 1; j<=r/2; j++){
                lines[r][j] = (lines[r-1][j-1] + lines[r-1][j]);
                lines[r][r-j] = (lines[r-1][j-1] + lines[r-1][j]);
            }
        }
    }
  cout << "Pascal Triangle (" << n << ") = {" << endl;

  // 4) print each row 0<=k<=n of the triangle in one line
  // for example, for n==4, your program should print 

  // 0 | 1
  // 1 | 1 1
  // 2 | 1 2 1
  // 3 | 1 3 3 1
  // 4 | 1 4 6 4 1
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            cout << lines[i][j] << ' ';
        }
        cout << endl;
    }

  cout << "}" << endl;

  // 5) delete all variables and/or arrays allocated in the stack
    delete[] lines;
  // 6) For debugging purposes, before you submit the assignment, run
  // your program for n=16 and compare the output with the example at
  // http://en.wikipedia.org/wiki/Pascal's_triangle .

  return 0;
}

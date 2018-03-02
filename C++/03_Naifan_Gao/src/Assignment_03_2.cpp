//
//  Assignment_03_2.cpp
//
//  Created by Gabriel Taubin on 9/20/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <limits>

using namespace std;

/////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

  cout << "------------------------------------------------------------" << endl;
  cout << "Problem 02_2" << endl;

  // Later in the course we will have to find an efficient algorithm
  // to solve the following problem: given a set of N 3D points p_1,
  // p_2,…,p_N, compute the distance from an arbitrary 3D point p, to
  // the closest point in the set. It is not necessary to identify
  // which point from the set is the closest to the given point. We
  // only want to know the distance. If this computation has to be
  // performed for a single point p, or even for a small number of
  // different points, the most efficient way of measuring the closest
  // distance is to measure the distance ‖p-p_k ‖ to each of the N
  // points of the set, and to determine the minimum. Note that the
  // complexity of this computation is linearly proportional to the
  // number of points N in the set, and it can be very time consuming
  // when the set of points is large. If the computation has to be
  // performed many times, say more than N, more efficient data
  // structures and algorithms must be used. We are not going to solve
  // this problem yet. Here we explore a simple special case.

  // 1) Create a 10x10x10 three-dimensional array on the heap of type
  // double
    double N = 10.0;
    double (* square)[10][10] = new double[10][10][10];
  // If you call the array dist, you should be able to access its
  // values as dist[i][j][k], where i,j,k are integers with values in
  // the range 0<=i,j,k<10

  // 2) Set the diagonal elements to 0 (i.e., N=10, and p_k=(k,k,k)
  // for k=1,2,…,10).
    for(int i = 0; i< N; i++){
        * (* (* (square+i)+i)+i) =static_cast<double>(0);
    }

  // 3) Fill the other elements of the three-dimensional array with
  // the distance to the nearest diagonal element, which in this
  // special case can be computed analytically.
    
    for(int r = 0; r < N; r++){
        for(int c = 0 ; c < N; c++){
            for(int h = 0; h < N; h++){
                double distance = numeric_limits<double>::max();
                for(int i = 0; i<10; i++){
                    double distance1 = static_cast<double>((r-i)*(r-i)+(c-i)*(c-i)+(h-i)*(h-i));
                    if (distance1 < distance){
                        distance = distance1;
                    }
                }
                * (* (* (square+r)+c)+h) = sqrt(distance);
            }
        }
    }

  // 4) Test your implementation by determining the distance from the
  // eight corners of the array to the nearest diagonal
  // element. Access these locations using only pointer arithmetic and
  // the dereference operator, *.
    
  // 5) the eight corners have coords (0,0,0),(0,0,9), ... (9,9,9)
  // for each corner (x,y,z), print a line
    int corner[2] = {0, 9};
  // int x=0,y=0,z=0;
  // cout << "dist from (" << x << "," << y << "," << z << ") = " << 
  //   dist[x][y][z] << endl;
    for(int i = 0; i<2; i++){
        for(int j = 0; j < 2; j++){
            for (int k = 0; k<2; k++){
                cout << "dist from (" << corner[i] << "," << corner[j] << "," << corner[k] << ")=" <<
                * (* (* (square+corner[i])+corner[j])+corner[k]) << endl;
            }
        }
    }

  // 6) Delete the array from the heap after testing.
    delete[] square;
  return 0;
}

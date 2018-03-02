#ifndef _SIMPLEGRAPHMAP_HPP_
#define _SIMPLEGRAPHMAP_HPP_
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

//typedef std::pair<int, int> MyPair;
//map<MyPair, int> myMap;

class SimpleGraphMap{
public:
    SimpleGraphMap(int N);
    ~SimpleGraphMap();
    void clear();
    //return (0<=jV && 0<=kV && jV!=kV && get(jV, kV)==-1)?value:-1
    int insert(int jV, int kV, int value);
    // if (jV, kV) is found, return the value associated with (jV, kV)
    // otherwise it returns -1
    int get(int jV, int kV) const;
private:
    int* first0;
    int* first1;
    int* first2;
    vector<int> values;
    int N;
};
#endif

#include <SimpleGraphMap.hpp>

//std::map<MyPair,int>::iterator it;
using namespace std;

SimpleGraphMap::SimpleGraphMap(int N){
    this->N = N;
    first0 = new int[(N+1)*(N+1)];
    first1 = new int[(N+1)*(N+1)];
    first2 = new int[(N+1)*(N+1)];
    fill_n(first0, (N+1)*(N+1), -1);
    fill_n(first1, (N+1)*(N+1), -1);
    fill_n(first2, (N+1)*(N+1), -1);
}

SimpleGraphMap::~SimpleGraphMap(){}

int SimpleGraphMap::get(int jV, int kV) const{
    int i1 = jV/(int)pow(N+1, 2);
    int j1 = (jV-i1*(N+1)*(N+1))/(N+1);
    int k1 = jV - j1*(N+1) - i1*(N+1)*(N+1);
    int i2 = kV/(int)pow(N+1, 2);
    int j2 = (kV-i2*(N+1)*(N+1))/(N+1);
    int k2 = kV - j2*(N+1) - i2*(N+1)*(N+1);
    if(abs(k2-k1)==1 && 0<=jV && 0<=kV && jV!=kV){
        int k = min(k1, k2);
        for(int start = first0[i1*(N+1)+j1]; start!=-1; start = values[start+2]){
            if(k==values[start]) return values[start+1];
        }
        return -1;
    }else if(abs(j2-j1)==1 && 0<=jV && 0<=kV && jV!=kV){
        int j = min(j1, j2);
        for(int start = first1[i1*(N+1)+k1]; start!=-1; start = values[start+2]){
            if(j==values[start]) return values[start+1];
        }
        return -1;
    }else if(abs(i2-i1)==1 && 0<=jV && 0<=kV && jV!=kV){
        int i = min(i1, i2);
        for(int start = first2[j1*(N+1)+k1]; start!=-1; start = values[start+2]){
            if(i==values[start]) return values[start+1];
        }
        return -1;
    }
    else return -1;
}

int SimpleGraphMap::insert(int jV, int kV, int value){
    if(jV>=0 && kV>=0 && jV!=kV && get(jV, kV)==-1){
        int i1 = jV/(int)pow(N+1, 2);
        int j1 = (jV-i1*(N+1)*(N+1))/(N+1);
        int k1 = jV - j1*(N+1) - i1*(N+1)*(N+1);
        int i2 = kV/(int)pow(N+1, 2);
        int j2 = (kV-i2*(N+1)*(N+1))/(N+1);
        int k2 = kV - j2*(N+1) - i2*(N+1)*(N+1);
        if(abs(k2-k1)==1 && i1==i2 && j1==j2){
            int k = min(k1, k2);
            int next = first0[i1*(N+1)+j1];
            first0[i1*(N+1)+j1] = values.size();
            values.push_back(k);
            values.push_back(value);
            values.push_back(next);
        }else if(abs(j2-j1)==1 && i1==i2 && k1==k2){
            int j = min(j1, j2);
            int next = first1[i1*(N+1)+k1];
            first1[i1*(N+1)+k1] = values.size();
            values.push_back(j);
            values.push_back(value);
            values.push_back(next);
        }else if(abs(i2-i1)==1 && j1==j2 && k1==k2){
            int i = min(i1, i2);
            int next = first2[j1*(N+1)+k1];
            first2[j1*(N+1)+k1] = values.size();
            values.push_back(i);
            values.push_back(value);
            values.push_back(next);
//        }
        }else return -1;
        return value;
    }
    return -1;
}

void SimpleGraphMap::clear(){
    values.clear();
}

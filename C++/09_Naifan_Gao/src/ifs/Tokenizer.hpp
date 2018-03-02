//
//  Tokenizer.hpp
//  ifsViewer2015
//
//  Created by Niko Gao on 11/2/17.
//

#ifndef Tokenizer_h
#define Tokenizer_h
#include <fstream>
#include <string>
using namespace std;
class Tokenizer: public string{
protected:
    ifstream& _ifstr;
    
public:
    Tokenizer(ifstream& ifstr):_ifstr(ifstr){}
    bool get();
    bool expecting(const string& str);
    unsigned getLineNum();
};

#endif /* Tokenizer_h */

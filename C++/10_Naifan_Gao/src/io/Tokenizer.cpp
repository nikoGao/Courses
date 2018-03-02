//
//  Tokenizer.cpp
//  ifs
//
//  Created by Niko Gao on 11/2/17.
//

#include <stdio.h>
#include "Tokenizer.hpp"

bool Tokenizer::get(){
    char c;
    if(_ifstr.peek()!=EOF){
        while(isspace(_ifstr.peek())||_ifstr.peek()==','){
            _ifstr.get();
        }
        if (_ifstr.peek()==EOF) {return 1;
        }else if(_ifstr.peek()=='{'||_ifstr.peek()=='}'||_ifstr.peek()=='['||_ifstr.peek()==']'){
            _ifstr.get(c);
            string str(1,c);
            str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
            str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
            this->std::__1::basic_string<char>::operator=(str);
        }else{
            string str = "";
            while(!isspace(_ifstr.peek())&&_ifstr.peek()!=','){
                str += _ifstr.get();
//            _ifstr.get(cstr, 512, ' ');
//            string str = cstr;
            }
            this->std::__1::basic_string<char>::operator=(str);
        }
        return 1;
    }else{
        return 0;
    }
}

bool Tokenizer::expecting(const string& str){
    this->erase(std::remove(this->begin(), this->end(), '\r'), this->end());
    this->erase(std::remove(this->begin(), this->end(), '\n'), this->end());
    return get() && (str==*this);
}



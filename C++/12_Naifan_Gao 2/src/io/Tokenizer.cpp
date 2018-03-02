//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:08:47 taubin>
//------------------------------------------------------------------------
//
// Tokenizer.cpp
//
// Software developed for the Fall 2017 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2017, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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


//Tokenizer::Tokenizer(ifstream& ifs):_skip(true) {
//
//  // TODO
//
//}
//
//bool Tokenizer::get() {
//
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//void Tokenizer::get(const string& errMsg) throw(StrException *) {
//  if(get()==false) throw new StrException(errMsg);
//}
//
//bool Tokenizer::getBool(bool& b) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::getFloat(float& f) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::getColor(Color& c) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::getVec4f(Vec4f& v) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::getVec3f(Vec3f& v) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::getVec2f(Vec2f& v) {
//  bool success = false;
//
//  // TODO
//
//  return success;
//}
//
//bool Tokenizer::equals(const string& str) {
//
//  // TODO
//
//  return false;
//}
//
//bool Tokenizer::expecting(const string& str) {
//  return get() && this->equals(str);
//}


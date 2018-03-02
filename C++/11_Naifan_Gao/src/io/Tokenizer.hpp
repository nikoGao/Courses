//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:13:15 taubin>
//------------------------------------------------------------------------
//
// Tokenizer.hpp
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

#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <wrl/Node.hpp>
#include "StrException.hpp"
using namespace std;

//class Tokenizer : public string {
//
//protected:
//
//  // TODO
//
//  bool  _skip; // if(_skip) skip comments
//
//public:
//
//  Tokenizer(ifstream&);
//
//  void setSkipComments(const bool value) { _skip = value; }
//
//  // a possible design; feel free to use your oun design
//
//  bool get();
//  void get(const string& errMsg) throw(StrException*);
//  bool getBool(bool& b);
//  bool getFloat(float& f);
//  bool getColor(Color& c);
//  bool getVec3f(Vec3f& v);
//  bool getVec4f(Vec4f& v);
//  bool getVec2f(Vec2f& v);
//  bool equals(const string& str);
//  bool expecting(const string& str);
//
//};
class Tokenizer: public string{
    protected:
    ifstream& _ifstr;
    
    public:
    Tokenizer(ifstream& ifstr):_ifstr(ifstr){}
    bool get();
    bool expecting(const string& str);
    unsigned getLineNum();
};
#endif // _TOKENIZER_HPP_

//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:29:13 taubin>
//------------------------------------------------------------------------
//
// IndexedFaceSet.cpp
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

#include <iostream>
#include <assert.h>
#include "IndexedFaceSet.hpp"

// VRML'97
//
// IndexedFaceSet {
//   eventIn       MFInt32 set_colorIndex
//   eventIn       MFInt32 set_coordIndex
//   eventIn       MFInt32 set_normalIndex
//   eventIn       MFInt32 set_texCoordIndex
//   exposedField  SFNode  color             NULL
//   exposedField  SFNode  coord             NULL
//   exposedField  SFNode  normal            NULL
//   exposedField  SFNode  texCoord          NULL
//   field         SFBool  ccw               TRUE
//   field         MFInt32 colorIndex        []        # [-1,)
//   field         SFBool  colorPerVertex    TRUE
//   field         SFBool  convex            TRUE
//   field         MFInt32 coordIndex        []        # [-1,)
//   field         SFFloat creaseAngle       0         # [ 0,)
//   field         MFInt32 normalIndex       []        # [-1,)
//   field         SFBool  normalPerVertex   TRUE
//   field         SFBool  solid             TRUE
//   field         MFInt32 texCoordIndex     []        # [-1,)
// }

IndexedFaceSet::IndexedFaceSet():
  _ccw(true),
  _convex(true),
  _creaseAngle(0),
  _solid(true),
  _normalPerVertex(true),
  _colorPerVertex(true)
{}

void IndexedFaceSet::clear() {
 
  // TODO

}

bool& IndexedFaceSet::getCcw()
{ return _ccw; }
bool& IndexedFaceSet::getConvex()
{ return _convex; }
float& IndexedFaceSet::getCreaseangle()
{ return _creaseAngle; }
bool& IndexedFaceSet::getSolid()
{ return _solid; }
bool& IndexedFaceSet::getNormalPerVertex()
{ return _normalPerVertex; }
bool& IndexedFaceSet::getColorPerVertex()
{ return _colorPerVertex; }
vector<float>& IndexedFaceSet::getCoord()
{ return _coord; }
vector<int>& IndexedFaceSet::getCoordIndex()
{ return _coordIndex; }
vector<float>& IndexedFaceSet::getNormal()
{ return _normal; }
vector<int>& IndexedFaceSet::getNormalIndex()
{ return _normalIndex; }
vector<float>& IndexedFaceSet::getColor()
{ return _color; }
vector<int>& IndexedFaceSet::getColorIndex()
{ return _colorIndex; }
vector<float>& IndexedFaceSet::getTexCoord()
{ return _texCoord; }
vector<int>& IndexedFaceSet::getTexCoordIndex()
{ return _texCoordIndex; }
int IndexedFaceSet::getNumberOfCoord()
{ return (int)(_coord.size()/3); }
int IndexedFaceSet::getNumberOfNormal()
{ return (int)(_normal.size()/3); }
int IndexedFaceSet::getNumberOfColor()
{ return (int)(_color.size()/3); }
int IndexedFaceSet::getNumberOfTexCoord()
{ return (int)(_texCoord.size()/2); }

int IndexedFaceSet::getNumberOfFaces()   {
  int nFaces = 0;

  // TODO
  // count number of -1's in coordIndex
    nFaces = count(_coordIndex.begin(), _coordIndex.end(), -1);
  return nFaces;
}

int IndexedFaceSet::getNumberOfCorners() {
  return 0; /* size of coordIndex - number of faces */
}
  
IndexedFaceSet::Binding IndexedFaceSet::getCoordBinding() {
  return PB_PER_VERTEX;
}
  
IndexedFaceSet::Binding IndexedFaceSet::getNormalBinding() {
  // if(normal.size()==0) {
  //   // NO_NORMALS
  // } else if(normalPerVertex==FALSE) {
  //   if(normalIndex.size()>0) {
  //     // NORMAL_PER_FACE_INDEXED;
  //     // assert(normalIndex.size()==getNumberOfFaces())
  //   } else {
  //     // NORMAL_PER_FACE;
  //     // assert(normal.size()/3==getNumberOfFaces())
  //   }
  // } else /* if(normalPerVertex==TRUE) */ {
  //   if(normalIndex.size()>0) {
  //     // NORMAL_PER_CORNER_INDEXED;
  //     // assert(normalIndex.size()==coordIndex.size())
  //   } else {
  //     // NORMAL_PER_VERTEX;
  //     // assert(normal.size()/3==coord.size()/3)
  //   }
  // }

  // TODO
    if(_normal.size()==0)
    return PB_NONE;
    else if(_normalPerVertex==false){
        if(_normalIndex.size()>0){
            //           if(_normalIndex.size()==getNumberOfFaces())
            assert(_normalIndex.size()==getNumberOfFaces());
            return PB_PER_FACE_INDEXED;
            //           else _normalBinding=PB_NONE;
        }
        else{
            //         if(_normal.size()/3==getNumberOfFaces())
            assert(_normal.size()/3==getNumberOfFaces());
            
            return PB_PER_FACE;
//            assert(_normal.size()/3==getNumberOfFaces());
            //         else _normalBinding = PB_NONE;
        }
    }
    else{ // if(normalPerVertex==TRUE)
        if(_normalIndex.size()>0){
            //           if(_normalIndex.size()==_coordIndex.size())
            assert(_normalIndex.size()==_coordIndex.size());
            return PB_PER_CORNER;
            //           else _normalBinding=PB_NONE;
            
        }
        else{
            //           if(_normal.size()/3==_coord.size()/3)
            assert(_normal.size()/3==_coord.size()/3);
            return PB_PER_VERTEX;
            //           else _normalBinding=PB_NONE;
            
        }
    }
}

IndexedFaceSet::Binding IndexedFaceSet::getColorBinding() {
  // if(color.size()==0) {
  //   // NO_COLORS
  // } else if(colorPerVertex==FALSE) {
  //   if(colorIndex.size()>0) {
  //     // COLOR_PER_FACE_INDEXED;
  //     // assert(colorIndex.size()==getNumberOfFaces())
  //   } else {
  //     // COLOR_PER_FACE;
  //     // assert(color.size()/3==getNumberOfFaces())
  //   }
  // } else /* if(colorPerVertex==TRUE) */ {
  //   if(colorIndex.size()>0) {
  //     // COLOR_PER_CORNER_INDEXED;
  //     // assert(colorIndex.size()==coordIndex.size())
  //   } else {
  //     // COLOR_PER_VERTEX;
  //     // assert(color.size()/3==coord.size()/3)
  //   }
  // }

  // TODO
    if(_color.size()==0)
    return PB_NONE;
    else if(_colorPerVertex==false){
        if(_colorIndex.size()>0){
            //           if(_colorIndex.size()==getNumberOfFaces())
            assert(_colorIndex.size()==getNumberOfFaces());
            return PB_PER_FACE_INDEXED;
            //           else _colorBinding=PB_NONE;
            
        }
        else{
            //           if(_color.size()/3==getNumberOfFaces())
            assert(_color.size()/3==getNumberOfFaces());
            return PB_PER_FACE;
            //           else _colorBinding=PB_NONE;
            
        }
    }
    else{ // if(colorPerVertex==TRUE)
        if(_colorIndex.size()>0){
            //           if(_colorIndex.size()==_coordIndex.size())
            assert(_colorIndex.size()==_coordIndex.size());
            return PB_PER_CORNER;
            //           else _colorBinding=PB_NONE;
            
        }
        else{
            //           if(_color.size()/3==_coord.size()/3)
            assert(_color.size()/3==_coord.size()/3);
            return PB_PER_VERTEX;
            //           else _colorBinding=PB_NONE;
            
        }
    }
}

IndexedFaceSet::Binding IndexedFaceSet::getTexCoordBinding() {
  // if(texCoord.size()==0) {
  //   // NO_TEX_COORD
  // } else if(texCoordIndex.size()>0) {
  //   // TEX_COORD_PER_CORNER_INDEXED;
  //   // assert(texCoordIndex.size()==coordIndex.size());
  // } else {
  //   // TEX_COORD_PER_VERTEX;
  //   // assert(texCoord.size()/3==coord.size()/3)
  // }

  // TODO
    if(_texCoord.size()==0)
    return PB_NONE;
    else if(_texCoordIndex.size()>0){
        //       if(_texCoordIndex.size()==_coordIndex.size())
        assert(_texCoordIndex.size()==_coordIndex.size());
        return PB_PER_CORNER;
        //       else _textCoordBinding=PB_NONE;
        
    }
    else{
        //       if(_texCoord.size()/3==_coord.size()/3)
        assert(_texCoord.size()/3==_coord.size()/3);
        return PB_PER_VERTEX;
        //       else _textCoordBinding=PB_NONE;
        
    }
}

void IndexedFaceSet::setNormalPerVertex(bool value) {
  _normalPerVertex = value;
}

void IndexedFaceSet::setColorPerVertex(bool value) {
  _colorPerVertex = value;
}

void IndexedFaceSet::printInfo(string indent) {
  std::cout << indent;
  if(_name!="") std::cout << "DEF " << _name << " ";
  std::cout << "IndexedFaceSet {\n";
  std::cout << indent << "  nFaces             = " <<
    getNumberOfFaces() << "\n";
  std::cout << indent << "  ccw                = " <<
    _ccw << "\n";
  std::cout << indent << "  convex             = " <<
    _convex << "\n";
  std::cout << indent << "  creaseAngle        = " <<
    _creaseAngle << "\n";
  std::cout << indent << "  solid              = " <<
    _solid << "\n";
  std::cout << indent << "  coordBinding       = " <<
    stringBinding(getCoordBinding()) << "\n";
  std::cout << indent << "  nCoord             = " <<
    _coord.size()/3 << "\n";
  std::cout << indent << "  coordIndex.size()  = " <<
    _coordIndex.size() << "\n";
  std::cout << indent << "  normalBinding      = " <<
    stringBinding(getNormalBinding()) << "\n";
  std::cout << indent << "  normalPerVertex    = " <<
    _normalPerVertex << "\n";
  std::cout << indent << "  nNormal            = " <<
    _normal.size()/3 << "\n";
  std::cout << indent << "  normalIndex.size() = " <<
    _normalIndex.size() << "\n";
  std::cout << indent << "  colorBinding       = " <<
    stringBinding(getColorBinding()) << "\n";
  std::cout << indent << "  colorPerVertex     = " <<
    _colorPerVertex << "\n";
  std::cout << indent << "  nColor             = " <<
    _color.size()/3 << "\n";
  std::cout << indent << "  colorIndex.size()  = " <<
    _colorIndex.size() << "\n";
  std::cout << indent << "  texCoordBinding    = " <<
    stringBinding(getTexCoordBinding()) << "\n";
  std::cout << indent << "  nTexCoord          = " <<
    _texCoord.size()/2 << "\n";
  std::cout << indent << "  texCoord.siZe()    = " <<
    _texCoordIndex.size() << "\n";
  std::cout << indent << "}\n";
}

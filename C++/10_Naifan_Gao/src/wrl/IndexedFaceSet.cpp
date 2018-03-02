//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-05 22:31:19 taubin>
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

// TODO ...
// Refactor your IfsViewer code
IndexedFaceSet::IndexedFaceSet() {
    /* remember to properly initialize all the class variables which do
     not have a default constructor */
    _ccw=true;
    _colorPerVertex=true;
    _convex=true;
    _creaseAngle=0.0f;
    _normalPerVertex=true;
    _solid=true;
}

void           IndexedFaceSet::clear() { _coord.clear();_coordIndex.clear();_normal.clear();_normalIndex.clear();_color.clear();_colorIndex.clear();_texCoord.clear();_texCoordIndex.clear();}
bool&          IndexedFaceSet::getCcw() { return _ccw;}
bool&          IndexedFaceSet::getConvex() { return _convex;}
float&         IndexedFaceSet::getCreaseangle() {return _creaseAngle; }
bool&          IndexedFaceSet::getSolid() { return _solid; }
bool&          IndexedFaceSet::getNormalPerVertex() { return _normalPerVertex; }
bool&          IndexedFaceSet::getColorPerVertex() { return _colorPerVertex; }
vector<float>& IndexedFaceSet::getCoord() { return _coord; }
vector<int>&   IndexedFaceSet::getCoordIndex() { return _coordIndex; }
vector<float>& IndexedFaceSet::getNormal() { return _normal; }
vector<int>&   IndexedFaceSet::getNormalIndex() { return _normalIndex; }
vector<float>& IndexedFaceSet::getColor() { return _color; }
vector<int>&   IndexedFaceSet::getColorIndex() { return _colorIndex; }
vector<float>& IndexedFaceSet::getTexCoord() { return _texCoord; }
vector<int>&   IndexedFaceSet::getTexCoordIndex() { return _texCoordIndex; }
int            IndexedFaceSet::getNumberOfFaces() { return count(_coordIndex.begin(), _coordIndex.end(), -1); }
int            IndexedFaceSet::getNumberOfCorners() { return _coord.size()/3; }
int            IndexedFaceSet::getNumberOfCoord() { return _coord.size()/3; }
int            IndexedFaceSet::getNumberOfNormal() { return _normal.size()/3; }
int            IndexedFaceSet::getNumberOfColor() { return _color.size()/3; }
int            IndexedFaceSet::getNumberOfTexCoord() { return _texCoord.size()/2; }
void           IndexedFaceSet::setNormalPerVertex(bool value) { _normalPerVertex=value; }
void           IndexedFaceSet::setColorPerVertex(bool value) { _colorPerVertex=value; }

IndexedFaceSet::Binding IndexedFaceSet::getNormalBinding() {
    if(_normal.size()==0)
        return PB_NONE;
    else if(_normalPerVertex==false){
        if(_normalIndex.size()>0){
            //           if(_normalIndex.size()==getNumberOfFaces())
            return PB_PER_FACE_INDEXED;
            //           else _normalBinding=PB_NONE;
            assert(_normalIndex.size()==getNumberOfFaces());
        }
        else{
            //         if(_normal.size()/3==getNumberOfFaces())
            return PB_PER_FACE;
            //         else _normalBinding = PB_NONE;
            assert(_normal.size()/3==getNumberOfFaces());
        }
    }
    else{ // if(normalPerVertex==TRUE)
        if(_normalIndex.size()>0){
            //           if(_normalIndex.size()==_coordIndex.size())
            return PB_PER_CORNER;
            //           else _normalBinding=PB_NONE;
            assert(_normalIndex.size()==_coordIndex.size());
        }
        else{
            //           if(_normal.size()/3==_coord.size()/3)
            return PB_PER_VERTEX;
            //           else _normalBinding=PB_NONE;
            assert(_normal.size()/3==_coord.size()/3);
        }
    }
}

// TODO
IndexedFaceSet::Binding IndexedFaceSet::getColorBinding() {
    if(_color.size()==0)
        return PB_NONE;
    else if(_colorPerVertex==false){
        if(_colorIndex.size()>0){
            //           if(_colorIndex.size()==getNumberOfFaces())
            return PB_PER_FACE_INDEXED;
            //           else _colorBinding=PB_NONE;
            assert(_colorIndex.size()==getNumberOfFaces());
        }
        else{
            //           if(_color.size()/3==getNumberOfFaces())
            return PB_PER_FACE;
            //           else _colorBinding=PB_NONE;
            assert(_color.size()/3==getNumberOfFaces());
        }
    }
    else{ // if(colorPerVertex==TRUE)
        if(_colorIndex.size()>0){
            //           if(_colorIndex.size()==_coordIndex.size())
            return PB_PER_CORNER;
            //           else _colorBinding=PB_NONE;
            assert(_colorIndex.size()==_coordIndex.size());
        }
        else{
            //           if(_color.size()/3==_coord.size()/3)
            return PB_PER_VERTEX;
            //           else _colorBinding=PB_NONE;
            assert(_color.size()/3==_coord.size()/3);
        }
    }
}

// TODO
IndexedFaceSet::Binding IndexedFaceSet::getTexCoordBinding() {
    if(_texCoord.size()==0)
        return PB_NONE;
    else if(_texCoordIndex.size()>0){
        //       if(_texCoordIndex.size()==_coordIndex.size())
        return PB_PER_CORNER;
        //       else _textCoordBinding=PB_NONE;
        assert(_texCoordIndex.size()==_coordIndex.size());
    }
    else{
        //       if(_texCoord.size()/3==_coord.size()/3)
        return PB_PER_VERTEX;
        //       else _textCoordBinding=PB_NONE;
        assert(_texCoord.size()/3==_coord.size()/3);
    }
}

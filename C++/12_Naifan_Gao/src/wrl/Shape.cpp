//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:29:12 taubin>
//------------------------------------------------------------------------
//
// Shape.cpp
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
#include "Shape.hpp"
#include "Appearance.hpp"

Shape::Shape():
  _appearance((Node*)0),
  _geometry((Node*)0) {
}

Shape::~Shape() {
}

Node* Shape::getAppearance() {

  // TODO
    return _appearance;

}

Node* Shape::getGeometry() {

  // TODO

  return _geometry;
}

bool Shape::hasAppearanceNone() {

  // TODO
    if(_appearance==(Node*)0) return true;
    return false;
}

bool Shape::hasAppearanceMaterial() {

  // TODO
    return _appearance->isMaterial();
}

bool Shape::hasAppearanceImageTexture() {

  // TODO
    return _appearance->isImageTexture();
}

bool Shape::hasAppearanceUnsupported() {

  // TODO
    if(!_appearance->isImageTexture() && !_appearance->isMaterial()) return true;
    return false;

}

bool Shape::hasGeometryNull() {

  // TODO
    if(_geometry==(Node*)0) return true;
    return false;
}

bool Shape::hasGeometryIndexedFaceSet() {

  // TODO
    if(_geometry->isIndexedFaceSet()) return true;
    return false;
}

bool Shape::hasGeometryIndexedLineSet() {

  // TODO
    if(_geometry->isIndexedLineSet()) return true;
    return false;
}

bool Shape::hasGeometryUnsupported() {

  // TODO
    if(!_geometry->isIndexedLineSet() && !_geometry->isIndexedFaceSet() && _geometry !=(Node*)0) return true;
    return false;
}

void Shape::setAppearance(Node* node) {

  // TODO
    _appearance = node;
}

void Shape::setGeometry(Node* node) {

  // TODO
    _geometry = node;
}

void Shape::printInfo(string indent) {
  std::cout << indent;
  if(_name!="") std::cout << "DEF " << _name << " ";
  std::cout << "Shape {\n";
  if(Node* appearance = getAppearance()) {
    std::cout << indent << "  appearance\n";
    appearance->printInfo(indent+"    ");
  }
  if(Node* geometry = getGeometry()) {
    std::cout << indent << "  geometry\n";
    geometry->printInfo(indent+"    ");
  }
  std::cout << indent << "}\n";
}
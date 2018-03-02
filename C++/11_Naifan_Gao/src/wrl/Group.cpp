//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:29:13 taubin>
//------------------------------------------------------------------------
//
// Group.cpp
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
#include <math.h>
#include <algorithm>
#include "Transform.hpp"
#include "Shape.hpp"
#include "IndexedFaceSet.hpp"
#include "IndexedLineSet.hpp"
#include <util/BBox.hpp>
  vector<float> Matrix;
Group::Group():
_bboxCenter(0.0f,0.0f,0.0f),
_bboxSize(-1.0f,-1.0f,-1.0f) {
}

Group::~Group() {

  // TODO
  // delete all children here
    _children.clear();
}

vector<pNode>& Group::getChildren() {
  return _children;
}

Node* Group::getChild(const string& name) const {
  Node* node = (Node*)0;

  // TODO
  // find child matching the given name
  // do not traverse any deeper
    for(int i=0; i< _children.size();i++){
        if(_children.at(i)->nameEquals(name)){
            node = _children.at(i);
            break;
        }
    }
  return node;
}

int Group::getNumberOfChildren() const {

  // TODO

  return _children.size();
}

pNode Group::operator[](const int i) {
  pNode node = (pNode)0;

  // TODO
  // return the i-th node, if 0<=i<getNumberOfChildren()
    node = _children.at(i);
  return node;
}

Vec3f& Group::getBBoxCenter() {

  // TODO
    return _bboxCenter;
}

Vec3f& Group::getBBoxSize() {

  // TODO
    return _bboxSize;
}

float Group::getBBoxDiameter() {
  float diam2 = 0.0f;

  // TODO
  // compute the square of the sdiameter of the sphere circumscribing
  // the bounding box
    diam2 = _bboxSize.x*_bboxSize.x+_bboxSize.y*_bboxSize.y+_bboxSize.z+_bboxSize.z;
  return (diam2>0.0f)?(float)sqrt(diam2):0.0f;
}

void Group::addChild(const pNode child) {

  // TODO
  // - add to the list of children, if not already there
  // - remember to set the parent of the child
    if(std::find(_children.begin(), _children.end(), child) == _children.end()) {
        _children.push_back(child);
    }
}

void Group::removeChild(const pNode child) {

  // TODO
  // look for chil in the list of children
  // if found, remove from the list and delete the child
    this->_children.erase(find(_children.begin(), _children.end(), child),_children.end());
  }


void Group::setBBoxCenter(Vec3f& value) {

  // TODO
    _bboxCenter=value;

}
void Group::setBBoxSize(Vec3f& value) {

  // TODO
    _bboxSize=value;
}

void Group::clearBBox() {

  // TODO
    Vec3f vec(0.0f,0.0f,0.0f);
    _bboxCenter = vec;
    Vec3f vec2(-1.0f,-1.0f,-1.0f);
    _bboxSize= vec2;
}
bool Group::hasEmptyBBox() const {

  // TODO
    if(_bboxSize.x==-1.0f && _bboxSize.y==-1.0f && _bboxSize.z==-1.0f)
        return true;
    return false;
}

void Group::appendBBoxCoord(vector<float>& coord) {

  // TODO

  // if the bbox is not empty, compute the coordinates of the eight
  // corners of the counding box, and append them to the coord array
    if(!hasEmptyBBox()){
        Vec3f size = getBBoxSize();
        Vec3f center = getBBoxCenter();
        coord.push_back(center.x-size.x/2);
        coord.push_back(center.y-size.y/2);
        coord.push_back(center.z-size.z/2);
        
        coord.push_back(center.x-size.x/2);
        coord.push_back(center.y+size.y/2);
        coord.push_back(center.z-size.z/2);
        
        coord.push_back(center.x-size.x/2);
        coord.push_back(center.y-size.y/2);
        coord.push_back(center.z+size.z/2);
        
        coord.push_back(center.x-size.x/2);
        coord.push_back(center.y+size.y/2);
        coord.push_back(center.z+size.z/2);
        
        coord.push_back(center.x+size.x/2);
        coord.push_back(center.y-size.y/2);
        coord.push_back(center.z-size.z/2);
        
        coord.push_back(center.x+size.x/2);
        coord.push_back(center.y+size.y/2);
        coord.push_back(center.z-size.z/2);
        
        coord.push_back(center.x+size.x/2);
        coord.push_back(center.y-size.y/2);
        coord.push_back(center.z+size.z/2);
        
        coord.push_back(center.x+size.x/2);
        coord.push_back(center.y+size.y/2);
        coord.push_back(center.z+size.z/2);
    }

}

void Group::updateBBox(vector<float>& coord) {

  // TODO

  // - update the bbox dimensions to also enclose the points contained
  //   in the coord array
  
  // - if the coord array does not contain any points, return without
  //   doing anything

  // - if the bounding box is empty, compute the bounding box of the
  //    points contained in the coord array
    if(coord.size()==0) return;
    if(hasEmptyBBox()){
        BBox* box = new BBox(3, coord, true);
        Vec3f size(box->getSide(), box->getSide(), box->getSide());
        Vec3f center(box->getCenter(0), box->getCenter(1), box->getCenter(2));
        setBBoxSize(size);
        setBBoxCenter(center);
    }

}
void Group::_updateBBox(vector<float> transformMatrix, float (&M)[16], double (&corners)[6], bool cube){
    int size = 0;
    float x_min=corners[0], x_max=corners[1], y_min=corners[2], y_max=corners[3], z_min=corners[4], z_max=corners[5];
    while(size < _children.size()){
        if(_children.at(size)->isShape()){
            Shape* shape = (Shape*)_children.at(size);
            if(shape->getGeometry()->isIndexedFaceSet()){
                IndexedFaceSet* node = dynamic_cast<IndexedFaceSet*>(shape->getGeometry());
                vector<float> new_node;
                for(int i = 0; i < node->getCoord().size(); i=i+3){
                    float coord[3]={node->getCoord().at(i), node->getCoord().at(i+1), node->getCoord().at(i+2)};
                    float x_temp = M[0]*coord[0]+M[1]*coord[1]+M[2]*coord[2] + M[3];
                    float y_temp = M[4]*coord[0]+M[5]*coord[1]+M[6]*coord[2] + M[7];
                    float z_temp = M[8]*coord[0]+M[9]*coord[1]+M[10]*coord[2] + M[11];
                    new_node.push_back(x_temp);new_node.push_back(y_temp);new_node.push_back(z_temp);
//                    if(x_temp>x_max) x_max=x_temp;
//                    else if(x_temp<x_min) x_min=x_temp;
//                    if(y_temp>y_max) y_max=y_temp;
//                    else if(y_temp<y_min) y_min=y_temp;
//                    if(z_temp>z_max) z_max=z_temp;
//                    else if(z_temp<z_min) z_min=z_temp;
                }
                BBox* box = new BBox(3, new_node, cube);
                if(box->getMin(0)<x_min)
                    corners[0]=box->getMin(0);
                if(box->getMax(0)>x_max)
                    corners[1]=box->getMax(0);
                if(box->getMin(1)<y_min)
                    corners[2]=box->getMin(1);
                if(box->getMax(1)>y_max)
                    corners[3]=box->getMax(1);
                if(box->getMin(2)<z_min)
                    corners[4]=box->getMin(2);
                if(box->getMax(2)>z_max)
                    corners[5]=box->getMax(2);
//                corners[0] = x_min; corners[1]= x_max; corners[2]=y_min; corners[3]=y_max;corners[4] = z_min; corners[5] = z_max;
                new_node.clear();
            }
        }else if(_children.at(size)->isTransform()){
            Transform* transform = (Transform*)_children.at(size);
            float temp[16];
            for(int i = 0; i< 16; i++){
                temp[i] = M[i];
            }
            copy(M, M+16, std::back_inserter(transformMatrix));
            int size = transformMatrix.size();
            transform->getMatrix(temp);
            for(int i=0; i< 16; i=i+4){
                M[i] = temp[i]*transformMatrix.at(size-16) + temp[i+1]*transformMatrix.at(size-12) + temp[i+2]*transformMatrix.at(size-8) + temp[i+3]*transformMatrix.at(size-4);
                M[i+1] = temp[i]*transformMatrix.at(size-15) + temp[i+1]*transformMatrix.at(size-11) + temp[i+2]*transformMatrix.at(size-7) + temp[i+3]*transformMatrix.at(size-3);
                M[i+2] = temp[i]*transformMatrix.at(size-14) + temp[i+1]*transformMatrix.at(size-10) + temp[i+2]*transformMatrix.at(size-6) + temp[i+3]*transformMatrix.at(size-2);
                M[i+3] = temp[i]*transformMatrix.at(size-13) + temp[i+1]*transformMatrix.at(size-9) + temp[i+2]*transformMatrix.at(size-5) + temp[i+3]*transformMatrix.at(size-1);
            }
            transform->_updateBBox(transformMatrix, M, corners, cube);
        }else if(_children.at(size)->isGroup()){
            Group* group = (Group*)_children.at(size);
            copy(M, M+16, std::back_inserter(transformMatrix));
            group->_updateBBox(transformMatrix, M, corners, cube);
        }
        if(size==_children.size()-1) {
            int i = 0;
            while(i<16){
                M[i] = transformMatrix.back();
                transformMatrix.pop_back();
                i++;
            }
        }
        size++;
    }
}

void Group::updateBBox(bool cube) {

  // TODO

  // compute the sdmallest bounding box containing
  // 1) all the coord of of geometry contained in Shape node children
  // 2) the 8 corners of the bounding boxes of the Group node children
  // 3) the 8 corners of the bounding boxes of the Transform node
  // children, after they are transformed to this Group coordinmate system
    float global_Matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    double init_corners[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    copy(global_Matrix, global_Matrix+16, std::back_inserter(Matrix));
    _updateBBox(Matrix, global_Matrix, init_corners, cube);
    Vec3f center(Vec3f((init_corners[0]+init_corners[1])/2, (init_corners[2]+init_corners[3])/2, (init_corners[4]+init_corners[5])/2));
    setBBoxCenter(center);
    Vec3f size(Vec3f(init_corners[1]-init_corners[0], init_corners[3]-init_corners[2], init_corners[5]-init_corners[4]));
    setBBoxSize(size);
    Matrix.clear();
}

// TODO
// can be used for debugging
// use as template to implement the method for other Node subclasses

void Group::printInfo(string indent) {
  std::cout << indent;
  if(_name!="") std::cout << "DEF " << _name << " ";
  std::cout << "Group {\n";
  std::cout << indent << "  " << "children [\n";
  int nChildren = getNumberOfChildren();
  for(int i=0;i<nChildren;i++) {
    Node* node = (*this)[i];
    node->printInfo(indent+"    ");
  }
  std::cout << indent << "  " << "]\n";
  std::cout << indent << "}\n";
}

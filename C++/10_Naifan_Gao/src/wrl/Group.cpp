//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-05 22:28:35 taubin>
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

#include "Transform.hpp"
#include "Shape.hpp"
#include "IndexedFaceSet.hpp"
#include <algorithm>
#include <math.h>
#include <util/BBox.hpp>
vector<float> Matrix;
// TODO ...
Group::Group(){
    _bboxCenter.operator=(Vec3f(0.0f,0.0f,0.0f));
    _bboxSize.operator=(Vec3f(-1.0f,-1.0f,-1.0f));
    _children.clear();
}

Group::~Group(){
    _children.clear();
}

vector<pNode>& Group::getChildren(){
    return _children;
}

unsigned Group::getNumberOfChildren(){
    return _children.size();
}

pNode Group::operator[](const int i){
    if(!_children.empty()) return _children.at(i);
    else return (Node*)0;
}

void  Group::addChild(pNode child){
    _children.push_back(child);
}
void Group::removeChild(pNode child){
    _children.erase(find(_children.begin(), _children.end(), child));
}

void Group::clearBBox(){
    _bboxCenter.operator=(Vec3f(0,0,0));
    _bboxSize.operator=(Vec3f(1,1,1));
}
bool  Group::hasEmptyBBox(){
    if(_bboxSize.x==-1.0f && _bboxSize.y==-1.0f && _bboxSize.z==-1.0f) return true;
    return false;
}

Vec3f& Group::getBBoxCenter(){
    return _bboxCenter;
}
Vec3f& Group::getBBoxSize(){
    return _bboxSize;
}
float Group::getBBoxDiameter(){
    return sqrt(_bboxSize.x*_bboxSize.x+_bboxSize.y*_bboxSize.y+_bboxSize.z*_bboxSize.z);
}

void Group::_updateBBox(vector<float> transformMatrix, float (&M)[16], double (&corners)[6]){
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
                BBox* box = new BBox(3, new_node, true);
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
            transform->_updateBBox(transformMatrix, M, corners);
        }else if(_children.at(size)->isGroup()){
            Group* group = (Group*)_children.at(size);
            copy(M, M+16, std::back_inserter(transformMatrix));
            group->_updateBBox(transformMatrix, M, corners);
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

void Group::updateBBox(){
//    P' = T * C * R * SR * S * -SR * -C * P
//    vector<float> Matrix;
    float global_Matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    double init_corners[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    copy(global_Matrix, global_Matrix+16, std::back_inserter(Matrix));
    _updateBBox(Matrix, global_Matrix, init_corners);
    _bboxCenter.operator=(Vec3f((init_corners[0]+init_corners[1])/2, (init_corners[2]+init_corners[3])/2, (init_corners[4]+init_corners[5])/2));
    _bboxSize.operator=(Vec3f(init_corners[1]-init_corners[0], init_corners[3]-init_corners[2], init_corners[5]-init_corners[4]));
    Matrix.clear();
}

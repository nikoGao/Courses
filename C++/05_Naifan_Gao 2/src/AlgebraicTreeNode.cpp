
//
//  AlgebraicTreeNode.cpp
//
//  Created by Gabriel Taubin on 9/27/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include "AlgebraicTreeNode.hpp"
#include <iostream>
using namespace std;
unsigned _ftoa(const double value, char* str){
    unsigned n = sprintf(str,"%.3f", value);
    return n;
}

AlgebraicTreeNode::AlgebraicTreeNode() {
    // TBD
    _parent=(AlgebraicTreeNode*)0;
    _childLeft =(AlgebraicTreeNode*)0;
    _childRight=(AlgebraicTreeNode*)0;
    _type=INVALID;
    _value=0.0;
}
AlgebraicTreeNode::~AlgebraicTreeNode(){
    cout << "Delete Node" <<this->getId()<< endl;
    delete this->_childLeft;
    delete this->_childRight;
}
AlgebraicTreeNode::AlgebraicTreeNode(const double value, AlgebraicTreeNode* parent) {
    // TBD
    _parent=parent;
    _value=value;
    _childLeft=(AlgebraicTreeNode*)0;
    _childRight=(AlgebraicTreeNode*)0;
    _type=NUMBER;
}
AlgebraicTreeNode::AlgebraicTreeNode(AlgebraicTreeNodeType operation, AlgebraicTreeNode* parent){
    _parent=parent;
    _value=0.0;
    _childLeft=(AlgebraicTreeNode*)0;
    _childRight=(AlgebraicTreeNode*)0;
    if(operation==ADD||operation==SUBTRACT||operation==MULTIPLY||operation==DIVIDE)
        _type=operation;
    else _type=INVALID;
}

void AlgebraicTreeNode::setParent(const AlgebraicTreeNode* parent){
    this->_parent=const_cast<AlgebraicTreeNode*>(parent);
}
void AlgebraicTreeNode::setChildLeft(const AlgebraicTreeNode* childLeft){
    this->_childLeft=const_cast<AlgebraicTreeNode*>(childLeft);
}
void AlgebraicTreeNode::setChildRight(const AlgebraicTreeNode* childRight){
    this->_childRight=const_cast<AlgebraicTreeNode*>(childRight);
}
bool AlgebraicTreeNode::isInvalid() const{
    if(this->_type==INVALID) return true;
    else return false;
}
bool AlgebraicTreeNode::isNumber() const{
    if(this->_type==NUMBER) return true;
    else return false;
}
bool AlgebraicTreeNode::isOperation() const{
    if(this->_type==ADD||this->_type==SUBTRACT||this->_type==MULTIPLY||this->_type==DIVIDE) return true;
    else return false;
}
void AlgebraicTreeNode::setId(int i){
    this->_id=i;
}
int AlgebraicTreeNode::getId() const{
    return this->_id;
}
char* AlgebraicTreeNode::toString() const {
    // TBD
    unsigned start = 0;
    unsigned count = 0;
    unsigned N = this->_toStringLength(start);
    char* str = new char[N];
    memset(str,'\0',N*sizeof(char));
    _toString(str, count);
    return str;
}
unsigned AlgebraicTreeNode::_toStringLength(unsigned int &len) const{
    static char stack[1024];
    if(!this->isInvalid()){
        if(this->isOperation()){
            len+=3;
            this->_childLeft->_toStringLength(len);
            this->_childRight->_toStringLength(len);
        }
        if(this->isNumber()){
            len += _ftoa(this->_value, stack);
        }
        return len;
    }else{
        return 1024;
    }
}
unsigned AlgebraicTreeNode::_toString(char* str, unsigned& counts) const{
    if(!this->isInvalid()){
        if(this->isNumber()){
            unsigned n = _ftoa(this->_value, str+counts);
            counts += n;
            return 1;
        }
        if(this->isOperation()){
            *(str+counts) = '(';
            counts++;
            this->_childLeft->_toString(str, counts);
            if(this->_type==ADD) *(str+counts) = '+';
            if(this->_type==SUBTRACT) *(str+counts) = '-';
            if(this->_type==MULTIPLY) *(str+counts) = '*';
            if(this->_type==DIVIDE) *(str+counts) = '/';
            counts++;
            this->_childRight->_toString(str, counts);
            *(str+counts) = ')';
            counts++;
        }
    }
}

double AlgebraicTreeNode::evaluate() const {
    // TBD
    if(!this->isInvalid()){
        if (this->isNumber()){
            return this->_value;
        }else if(this->isOperation()){
            if(this->_type==ADD)
                return this->_childLeft->evaluate() + this->_childRight->evaluate();
            if(this->_type==SUBTRACT)
                return this->_childLeft->evaluate() - this->_childRight->evaluate();
            if(this->_type==MULTIPLY)
                return this->_childLeft->evaluate() * this->_childRight->evaluate();
            if(this->_type==DIVIDE)
                return this->_childLeft->evaluate() / this->_childRight->evaluate();
        }
    }
}

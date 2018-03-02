//
//  AlgebraicTreeUnary.cpp
//  ALL_BUILD
//
//  Created by Niko Gao on 10/13/17.
//
#include "AlgebraicTreeUnary.hpp"
#include <stdio.h>

AlgebraicTreeUnary::~AlgebraicTreeUnary(){
    delete _child;
}

AlgebraicTreeUnary::AlgebraicTreeUnary(AlgebraicUnaryOperator operand){
    _operand = operand;
    _child = (AlgebraicTreeNode*)0;
}

const bool AlgebraicTreeUnary::isNumber() const{
    return false;
}

const bool AlgebraicTreeUnary::isOperation() const{
    return false;
}

const bool AlgebraicTreeUnary::isUnary() const{
    return true;
}

double AlgebraicTreeUnary::evaluate() const{
    double value = 0.0;
    if(_operand==SIN) value += sin(_child->evaluate());
    else if(_operand==COS) value += cos((_child->evaluate()));
    else if(_operand==SQRT) value += sqrt(_child->evaluate());
    else if(_operand==TAN) value += tan((_child->evaluate()));
    return value;
}

unsigned AlgebraicTreeUnary::toStringLength() const{
    int length = 0;
    if(_operand==SIN || _operand==COS || _operand==TAN) length += 5 + _child->evaluate();
    if(_operand==SQRT) length += 6 + _child->evaluate();
    return length;
}

unsigned AlgebraicTreeUnary::toString(char &str) const{
    char* strPtr = &str;
    // TBD
    if(_operand==SIN){
        *(strPtr) = 's';
        *(strPtr+1) = 'i';
        *(strPtr+2) = 'n';
        strPtr += 3;
    }
    if(_operand==COS){
        *(strPtr) = 'c';
        *(strPtr+1) = 'o';
        *(strPtr+2) = 's';
        strPtr += 3;
    }
    if(_operand==SQRT){
        *(strPtr) = 's';
        *(strPtr+1) = 'q';
        *(strPtr+2) = 'r';
        *(strPtr+3) = 't';
        strPtr += 4;
    }
    if(_operand==TAN){
        *(strPtr) = 't';
        *(strPtr+1) = 'a';
        *(strPtr+2) = 'n';
        strPtr += 3;
    }
    if(_child->isNumber()||_child->isUnary()){
        *strPtr = '(';
        strPtr++;
    }
    strPtr += _child->toString(*strPtr);
    if(_child->isNumber()){
        *strPtr = ')';
        strPtr++;
    }
    return strPtr-&str;
}

void AlgebraicTreeUnary::setType(AlgebraicUnaryOperator operand){
    _operand = operand;
}

void AlgebraicTreeUnary::setChild(AlgebraicTreeNode *child){
    _child = child;
}

AlgebraicTreeNode* AlgebraicTreeUnary::getChild(){
    return _child;
}

AlgebraicTreeNode** AlgebraicTreeUnary::getChildPtr(){
    return &_child;
}

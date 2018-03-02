#include "AlgebraicTreeOperation.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

 AlgebraicTreeOperation::~AlgebraicTreeOperation() {
   // TBD
}

AlgebraicTreeOperation::AlgebraicTreeOperation(AlgebraicTreeOperationType operation) {
  _childLeft = (AlgebraicTreeNode*)0;
  _childRight = (AlgebraicTreeNode*)0;
  if (operation == ADD || operation == SUBTRACT || operation == MULTIPLY || operation == DIVIDE)
  {
    _type = operation;
  }
  else _type = ZERO;
  //_value = 0.0;
}

const bool AlgebraicTreeOperation::isNumber() const {
  return false;
}

const bool AlgebraicTreeOperation::isOperation() const {
  return true;
}

double AlgebraicTreeOperation::evaluate() const {
  double value = 0.0f;
    if(_type == ADD)
    {
        double left = _childLeft->evaluate();
        double right = _childRight->evaluate();
        //cout << "node" << _id << " : (" << left << "+" << right << ")=" << left + right << endl;
        value = left + right;
        return value;
    }
    else if(_type == SUBTRACT)
    {
        double left = _childLeft->evaluate();
        double right = _childRight->evaluate();
        //cout << "node" << _id << " : (" << left << "-" << right << ")=" << left - right << endl;
        value = left - right;
        return value;
    }
    else if(_type == MULTIPLY)
    {
        double left = _childLeft->evaluate();
        double right = _childRight->evaluate();
        //cout << "node" << _id << " : (" << left << "*" << right << ")=" << left * right << endl;
        value = left * right;
        return value;
    }
    else if(_type == DIVIDE)
    {
        double left = _childLeft->evaluate();
        double right = _childRight->evaluate();
        //cout << "node" << _id << " : (" << left << "/" << right << ")=" << left / right << endl;
        value = left / right;
        return value;
    }
    else
    {
        cout << "INVALID" << endl;
        return 0;
    }
  //return value;
}

unsigned AlgebraicTreeOperation::toStringLength() const {
  unsigned length = 0;
    if (this->isOperation())
    {
        if(this ->_childLeft)
        {
            length++;
            length += this->_childLeft->toStringLength();
        }
        length++;
        if(this ->_childRight)
        {
            length += this->_childRight->toStringLength();
            length++;
        }
    }
  return length;
}

unsigned AlgebraicTreeOperation::toString(char& str) const {
  char* strPtr = &str;
    //unsigned i = 0;
    if(this ->_childLeft)
    {
        *(strPtr) = '(';
        strPtr++;
        strPtr = strPtr + this->_childLeft->toString(*strPtr);
    }
    if(_type == ADD)
        *(strPtr) = '+';
    if(_type == SUBTRACT)
        *(strPtr) = '-';
    if(_type == MULTIPLY)
        *(strPtr) = '*';
    if(_type == DIVIDE)
        *(strPtr) = '/';
    strPtr++;
    if(this ->_childRight)
    {
        strPtr = strPtr + this->_childRight->toString(*(strPtr));
        *(strPtr) = ')';
        strPtr++;
    }
  return strPtr-&str;
}

void AlgebraicTreeOperation::setType(AlgebraicTreeOperationType type) {
  this->_type = type;
}

void AlgebraicTreeOperation::setChildLeft(AlgebraicTreeNode* childLeft) {
    this->_childLeft = childLeft;
}

void AlgebraicTreeOperation::setChildRight(AlgebraicTreeNode* childRight) {
    this->_childRight = childRight;
}

AlgebraicTreeNode* AlgebraicTreeOperation::getChildLeft() {
  return _childLeft;
}

AlgebraicTreeNode* AlgebraicTreeOperation::getChildRight() {
  return _childRight;
}

AlgebraicTreeNode** AlgebraicTreeOperation::getChildLeftPtr() {
  return &_childLeft;
}

AlgebraicTreeNode** AlgebraicTreeOperation::getChildRightPtr() {
  return &_childRight;
}

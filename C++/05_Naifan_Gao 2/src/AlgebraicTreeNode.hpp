//
//  AlgebraicTreeNode.hpp
//
//  Created by Gabriel Taubin on 9/27/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#ifndef _AlgebraicTreeNode_hpp_
#define _AlgebraicTreeNode_hpp_

#include <string.h>
#include <math.h>
#include <cstring>
#include <cstdio>
#include <stdio.h>
enum AlgebraicTreeNodeType {
  INVALID, NUMBER, ADD, SUBTRACT, MULTIPLY, DIVIDE
};
unsigned _ftoa(const double value, char* str = (char*)0);
class AlgebraicTreeNode {

public:

  // default constructor
  AlgebraicTreeNode();
  //constructor for value
  AlgebraicTreeNode(const double, AlgebraicTreeNode* parent=(AlgebraicTreeNode*)0);
  //operator constructor
  AlgebraicTreeNode(AlgebraicTreeNodeType, AlgebraicTreeNode* parent=(AlgebraicTreeNode*)0);
  // destructor
  ~AlgebraicTreeNode();
  // string representation
  void DestoryTreeNode(AlgebraicTreeNode* parent);
  void setParent(const AlgebraicTreeNode* parent);
  void setChildLeft(const AlgebraicTreeNode* childLeft);
  void setChildRight(const AlgebraicTreeNode* childRight);
    //toString
  char* toString() const;
  // evaluator
  double evaluate() const;
  bool isInvalid() const;
  bool isNumber() const;
  bool isOperation() const;
  void setId(int);
  int getId() const;
  

private:

  AlgebraicTreeNode* 	_parent;
  AlgebraicTreeNodeType	_type;
  double             	_value;
  AlgebraicTreeNode* 	_childLeft;
  AlgebraicTreeNode* 	_childRight;
  int                   _id;
  unsigned _toStringLength(unsigned&) const;
  unsigned _toString(char* str,unsigned&) const;

};

#endif // _AlgebraicTreeNode_hpp_

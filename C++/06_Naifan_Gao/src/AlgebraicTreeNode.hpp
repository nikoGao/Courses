#ifndef _AlgebraicTreeNode_hpp_
#define _AlgebraicTreeNode_hpp_

#define FTOA_BUFFER_LENGTH 1024
#define FTOA_FORMAT "%.4f"


#include <string.h>
#include <math.h>
#include <iostream>
#include <ctype.h>
using namespace std;

unsigned _ftoa(const double value, char* str=(char*)0);
enum AlgebraicTreeNodeType {
  INVALID,NUMBER,ADD,SUBTRACT,MULTIPLY,DIVIDE
};

class AlgebraicTreeNode {

public:

  // destructor
  ~AlgebraicTreeNode();

  // empty constructor
  AlgebraicTreeNode();

  // construct a NUMBER node
  AlgebraicTreeNode(const double value);

  // construct a ADD,SUBTRACT,MULTIPLY, or DIVIDE node
  AlgebraicTreeNode(const AlgebraicTreeNodeType type);

  // parser constructor
  AlgebraicTreeNode(const char* expression);

  //copy constructor
  AlgebraicTreeNode(AlgebraicTreeNode& src);
  AlgebraicTreeNode* copyTree(AlgebraicTreeNode*& oldNode);

  // setter
  void setParent(AlgebraicTreeNode* parent);
  void setChildLeft(AlgebraicTreeNode* childLeft);
  void setChildRight(AlgebraicTreeNode* childRight);

  double evaluate() const;

  char* toString() const;
                    
  const bool isInvalid() const;
  const bool isNumber() const;
  const bool isOperation() const;

  const bool isRoot() const;
  const bool isLeftChild() const;
  const bool isRightChild() const;

private:

  AlgebraicTreeNodeType _type;
  double                _value;
  AlgebraicTreeNode*    _parent;
  AlgebraicTreeNode*    _childLeft;
  AlgebraicTreeNode*    _childRight;

  unsigned _parseExpression(const char* expression);
  unsigned _parseNumber(const char* expression);
  unsigned _toStringLength() const;
  unsigned _toString(char* str) const;

  // HINT:
  // implement these private methods and use them in the
  // implementation of some of the public methods defined above
  // 
  // It will be OK to design your implementation withou implementing
  // these methods
  // 
  // unsigned _toStringLength() const;
  // unsigned _toString(char* str) const;

};

// HINT:
// implement these global method and use it in the implementation of
// some of the public methods defined above
// 


#endif // _AlgebraicTreeNode_hpp_

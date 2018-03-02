// AlgebraicTreeExpression.cpp
#include "AlgebraicTreeExpression.hpp"

AlgebraicTreeExpression::~AlgebraicTreeExpression() {
  if(_root!=(AlgebraicTreeNode*)0) delete _root;
}

AlgebraicTreeExpression::AlgebraicTreeExpression():
  _root(new AlgebraicTreeNode()) {
}

double AlgebraicTreeExpression::evaluate() const {
  return _root->evaluate();
}

char* AlgebraicTreeExpression::toString() const {
  return _root->toString();
}

// parser constructor
AlgebraicTreeExpression::AlgebraicTreeExpression(const char* expression):
  _root(new AlgebraicTreeNode(expression)) {
}

// copy constructor
AlgebraicTreeExpression::AlgebraicTreeExpression(AlgebraicTreeExpression& src) {
  // TBD
    _root = new AlgebraicTreeNode(*src._root);
}

// assignment operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::operator=(AlgebraicTreeExpression& src) {
  // TBD
    AlgebraicTreeExpression temp(src);
    this->swap(temp);
    return *this;
}

// swap operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::swap(AlgebraicTreeExpression& src) {
  // TBD
    if(this->_root==src._root) return *this;
    else{
        AlgebraicTreeNode* a = src._root;
        src._root = this->_root;
        this->_root = a;
        return *this;
    }
}

// increment operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::operator+=(AlgebraicTreeExpression& src) {
  // TBD
    this->_operatorInPlace(ADD,src);
    return *this;
}

// decrement operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::operator-=(AlgebraicTreeExpression& src) {
  // TBD
    this->_operatorInPlace(SUBTRACT,src);
    return *this;
}

// multiplication in place operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::operator*=(AlgebraicTreeExpression& src) {
  // TBD
    this->_operatorInPlace(MULTIPLY,src);
    return *this;
}

// division in place operator
AlgebraicTreeExpression&
AlgebraicTreeExpression::operator/=(AlgebraicTreeExpression& src) {
  // TBD
    this->_operatorInPlace(DIVIDE,src);
    return *this;
}


AlgebraicTreeExpression&
AlgebraicTreeExpression::_operatorInPlace(AlgebraicTreeNodeType type,AlgebraicTreeExpression& src){
    AlgebraicTreeNode* root = new AlgebraicTreeNode(type);
    root->setChildLeft(this->_root);
    AlgebraicTreeExpression temp(src);
    root->setChildRight(new AlgebraicTreeNode(*temp._root));
    this->_root = root;
    return *this;
}

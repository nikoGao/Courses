#include "AlgebraicTreeNode.hpp"

//int AlgebraicTreeNode::n = 0;

AlgebraicTreeNode::~AlgebraicTreeNode() {
  //
}

AlgebraicTreeNode::AlgebraicTreeNode() {
  _parent = (AlgebraicTreeNode*)0;
  _invalid = false;
}

const bool AlgebraicTreeNode::isRoot() const {
  return false; // TBD
}

const bool AlgebraicTreeNode::isInvalid() const {
  if(_invalid)
    return true;
  else return false;
}

const bool AlgebraicTreeNode::isNumber() const {
  return false;
}

const bool AlgebraicTreeNode::isOperation() const {
    return false;
}

void AlgebraicTreeNode::setInvalid(bool value) {
  this->_invalid = value;
}

void AlgebraicTreeNode::setParent(AlgebraicTreeNode* parent) {
  this->_parent = parent;
}


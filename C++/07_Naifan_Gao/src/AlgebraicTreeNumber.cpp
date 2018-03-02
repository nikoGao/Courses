#include <stdio.h>
#include "AlgebraicTreeNumber.hpp"

// remember that
// class AlgebraicTreeNumber : public AlgebraicTreeNode {

AlgebraicTreeNumber::~AlgebraicTreeNumber() {
  // TBD
}

AlgebraicTreeNumber::AlgebraicTreeNumber(const double value) {
  // TBD
    this->_value = value;
}

const bool AlgebraicTreeNumber::isNumber() const {
  return true; // TBD
}

const bool AlgebraicTreeNumber::isOperation() const {
  return false; // TBD
}

const bool AlgebraicTreeNumber::isUnary() const{
    return false;
}

double AlgebraicTreeNumber::evaluate() const {
  return this->_value; // TBD
}

unsigned AlgebraicTreeNumber::toStringLength() const {
  static char buff[BUFF_LENGTH];
  // TBD
  // 1) fill the buffer with the string representation of the node
  // 2) return the length of the resulting string
    unsigned length = sprintf(buff,NUMBER_FORMAT,this->_value);
  return length;
}

unsigned AlgebraicTreeNumber::toString(char& str) const {
  // TBD
  // 1) fill the str argument the string representation of the node
  // 2) return the length of the resulting string
    unsigned n = sprintf(&str,NUMBER_FORMAT,this->_value);
  return n;
}

void AlgebraicTreeNumber::setValue(double value) {
  // TBD
    this->_value = value;
}


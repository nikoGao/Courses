#include <stdio.h>
#include <iostream>
#include "AlgebraicTreeNumber.hpp"

// remember that
// class AlgebraicTreeNumber : public AlgebraicTreeNode {

using namespace std;

AlgebraicTreeNumber::~AlgebraicTreeNumber() {
  // TBD
}

AlgebraicTreeNumber::AlgebraicTreeNumber(const double value) {
    this->_value = value;
}

const bool AlgebraicTreeNumber::isNumber() const {
  return true; // TBD
}

const bool AlgebraicTreeNumber::isOperation() const {
  return false; // TBD
}

double AlgebraicTreeNumber::evaluate() const {
    //cout  << _value << endl;
    return this->_value;
}

unsigned AlgebraicTreeNumber::toStringLength() const {
  static char buff[BUFF_LENGTH];
    //memset(buff,'\0',FTOA_BUFFER_LENGTH*sizeof(char));
    unsigned length = sprintf(buff,NUMBER_FORMAT,_value);
    return length;
}

unsigned AlgebraicTreeNumber::toString(char& str) const {
  // TBD
  // 1) fill the str argument the string representation of the node
  // 2) return the length of the resulting string
    //memset(buff,'\0',FTOA_BUFFER_LENGTH*sizeof(char));
    unsigned length = sprintf(&str,NUMBER_FORMAT,_value);
    return length;
}

void AlgebraicTreeNumber::setValue(double value) {
  this->_value = value;
}


#include <stdlib.h>
#include <string.h>
#include "AlgebraicTreeExpression.hpp"
#include "AlgebraicTreeNode.hpp"
#include "AlgebraicTreeNumber.hpp"
#include "AlgebraicTreeOperation.hpp"
AlgebraicTreeExpression::~AlgebraicTreeExpression() {
  if(_root!=(AlgebraicTreeNode*)0)
      delete _root;
}

AlgebraicTreeExpression::AlgebraicTreeExpression(){
}

bool AlgebraicTreeExpression::isEmpty() const {
  if(this->_root->isInvalid())
    return true;
  else
    return false; // TBD
}

double AlgebraicTreeExpression::evaluate() const {
  return this->_root->evaluate();
}

char* AlgebraicTreeExpression::toString() const {
  unsigned N = this->_root->toStringLength();
  char *str = new char[N + 1];
  memset(str, '\0', (N + 1) * sizeof(char));
  char& p = *str;
  this->_root->toString(p);
  return str;
}

void AlgebraicTreeExpression::setRoot(AlgebraicTreeNode* root) {
  this->_root = root;
}

AlgebraicTreeExpression::AlgebraicTreeExpression(const char* expression):
_root((AlgebraicTreeNode*)0)
{
  unsigned length = _parse(expression, &this->_root);
}

unsigned AlgebraicTreeExpression::_parse
(const char* expression, AlgebraicTreeNode** nodePtr) {
  unsigned length = 0;
  char*    ptr = (char*)expression;
  bool     onlyCheckSyntax = (*nodePtr==(AlgebraicTreeNode*)0);
//  if(onlyCheckSyntax==true) {
    //unsigned length = 0;
    unsigned i = 0;
    unsigned m = 0, n = 0;
    if(*(expression + i) == '(') {
      for (i = 0; *(expression + i) != '\0'; i++) {
        if (*(expression + i) == '(') {
          m++;
        } else if (*(expression + i) == ')') {
          n++;
        } else {
          if (m - n == 1) {
            if(*(expression + i) == 'e'){
              i++;
              continue;
            }
            if(*(expression + i) == '-' && *(expression + i - 1) == '('){
              i++;
              continue;
            }
            if (*(expression + i) == '+') {
              AlgebraicTreeOperation *opnode = new AlgebraicTreeOperation();
              if (onlyCheckSyntax)
                setRoot(opnode);
              else
                *nodePtr = opnode;
              opnode->setType(ADD);
              opnode->setChildLeft(new AlgebraicTreeOperation());
              opnode->setChildRight(new AlgebraicTreeOperation());
              length = length + this->_parse(expression + 1, opnode->getChildLeftPtr());
              length = length + this->_parse(expression + 1 + i, opnode->getChildRightPtr());
              length += 3;
              break;
            } else if (*(expression + i) == '-') {
              AlgebraicTreeOperation *opnode = new AlgebraicTreeOperation();
              if (onlyCheckSyntax)
                setRoot(opnode);
              else
                *nodePtr = opnode;
              opnode->setType(SUBTRACT);
              opnode->setChildLeft(new AlgebraicTreeOperation());
              opnode->setChildRight(new AlgebraicTreeOperation());
              length = length + this->_parse(expression + 1, opnode->getChildLeftPtr());
              length = length + this->_parse(expression + 1 + i, opnode->getChildRightPtr());
              length += 3;
              break;
            } else if (*(expression + i) == '*') {
              AlgebraicTreeOperation *opnode = new AlgebraicTreeOperation();
              if (onlyCheckSyntax)
                setRoot(opnode);
              else
                *nodePtr = opnode;
              opnode->setType(MULTIPLY);
              opnode->setChildLeft(new AlgebraicTreeOperation());
              opnode->setChildRight(new AlgebraicTreeOperation());
              length = length + this->_parse(expression + 1, opnode->getChildLeftPtr());
              length = length + this->_parse(expression + 1 + i, opnode->getChildRightPtr());
              length += 3;
              break;
            } else if (*(expression + i) == '/') {
              AlgebraicTreeOperation *opnode = new AlgebraicTreeOperation();
              if (onlyCheckSyntax)
                setRoot(opnode);
              else
                *nodePtr = opnode;
              opnode->setType(DIVIDE);
              opnode->setChildLeft(new AlgebraicTreeOperation());
              opnode->setChildRight(new AlgebraicTreeOperation());
              length = length + this->_parse(expression + 1, opnode->getChildLeftPtr());
              length = length + this->_parse(expression + 1 + i, opnode->getChildRightPtr());
              length += 3;
              break;
            }
          }
        }
      }
      return length;
    }
    else {
      AlgebraicTreeNumber* num = new AlgebraicTreeNumber();
      if(onlyCheckSyntax)
        setRoot(num);
      else
        *nodePtr = num;
      //this->_type = NUMBER;
      unsigned length = 0;
      const char* begPtr = expression;
      char* endPtr;
      double value = strtod(begPtr, &endPtr);
      length = endPtr - begPtr;
      num->setValue(value);
      return length;
    }
    if (m != n)
    {
      return length = 0;
    }
    //return length;
  } //else /* if(onlyCheckSyntax==false) */ {
    // TBD
  //}
  //return length;
//}


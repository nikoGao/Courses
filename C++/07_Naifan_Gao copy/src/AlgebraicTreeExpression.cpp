#include <stdlib.h>
#include <string.h>
#include "AlgebraicTreeExpression.hpp"

AlgebraicTreeExpression::~AlgebraicTreeExpression() {
  // TBD
}

AlgebraicTreeExpression::AlgebraicTreeExpression() {
  // TBD
    _root = (AlgebraicTreeNode*)0;
}

bool AlgebraicTreeExpression::isEmpty() const {
  return false; // TBD
}

double AlgebraicTreeExpression::evaluate() const {
    if(this->_root->isNumber()) return this->_root->evaluate();
    if(this->_root->isOperation()) return this->_root->evaluate();
  return 0.0; // TBD
}

char* AlgebraicTreeExpression::toString() const {
  // TBD
    unsigned N = this->_root->toStringLength();
    char* str = new char[N];
    memset(str,'\0',N*sizeof(char));
    this->_root->toString(*str);
  return str;
}

void AlgebraicTreeExpression::setRoot(AlgebraicTreeNode* root) {
  // TBD
    this->_root = root;
}

AlgebraicTreeExpression::AlgebraicTreeExpression(const char* expression) {
  // TBD
    unsigned length = 0;
    unsigned strLength = string(expression).length();
    unsigned i = 0;
    unsigned parenthese = 0;
    while(isspace(*(expression+length))) length++;
    while(i < strLength){
        if(*(expression+i)=='(') parenthese++;
        if(*(expression+i)==')') parenthese--;
        i++;
    }
    length += _parse(expression+length, &this->_root);
    if(length < strLength || parenthese != 0){
        this->_root->setInvalid(true);
        delete this;
    }
}

unsigned AlgebraicTreeExpression::_parse
(const char* expression, AlgebraicTreeNode** nodePtr) {
  unsigned length = 0;
  char*    ptr = (char*)expression;
  bool     onlyCheckSyntax = (*nodePtr==(AlgebraicTreeNode*)0);
    unsigned strlen = 0;
    unsigned len = string(ptr).length();
    while(isspace(*(ptr+length))) length++;
    strlen = length;
//  if(onlyCheckSyntax==true) {
//    // TBD
//
//  } else /* if(onlyCheckSyntax==false) */ {
    // TBD
      if(*(ptr+strlen) == '('){
          while(isspace(*(ptr+strlen+1))) strlen++;
          if(*(ptr+strlen+1) == '('){
              int parentheses = 0;
              bool isOperator = false;
              while(!isOperator){
                  strlen++;
                  if(*(ptr+strlen) == '(') parentheses++;
                  else if(*(ptr+strlen)== ')') parentheses--;
                  if(parentheses==0) isOperator=true;
              }
              if(strlen >= len) return 0;
              else{
                  strlen++;
                  while(isspace(*(expression+strlen))){
                      strlen++;
                  }
                  AlgebraicTreeOperation* operation =new AlgebraicTreeOperation();
                  if(*(expression+strlen)=='+') operation->setType(ADD);
                  if(*(expression+strlen)=='-') operation->setType(SUBTRACT);
                  if(*(expression+strlen)=='*') operation->setType(MULTIPLY);
                  if(*(expression+strlen)=='/') operation->setType(DIVIDE);
                  if(onlyCheckSyntax==true) setRoot(operation);
                  else *nodePtr = operation;
                  operation->setChildLeft(new AlgebraicTreeOperation());
                  unsigned cl = _parse(expression+1, operation->getChildLeftPtr());
                  operation->setChildRight(new AlgebraicTreeOperation());
                  unsigned cr = _parse(expression+strlen+1,operation->getChildRightPtr());
                  length += 2 + cl + cr;
                  while(*(expression+length)==')') length++;
                  return length;
              }
          }else{
              int space = length;
              while(isspace(*(expression+length))){
                  length++;
                  space++;
              }
              unsigned start = 1;
              do{
                  start++;
                  if(start > string(expression).length()|| *(expression+start)==')') return 0;
                  if(*(expression+start-1)=='e') start++;
                  if(isspace(*(expression+start))) length++;
              }while(*(expression+start)!='+' && *(expression+start)!='-' && *(expression+start)!='*' && *(expression+start)!='/');
              AlgebraicTreeOperation* operation = new AlgebraicTreeOperation();
              if(*(expression+start)=='+') operation->setType(ADD);
              if(*(expression+start)=='-') operation->setType(SUBTRACT);
              if(*(expression+start)=='*') operation->setType(MULTIPLY);
              if(*(expression+start)=='/') operation->setType(DIVIDE);
              length += 2;
              if(onlyCheckSyntax==true) this->setRoot(operation);
              else *nodePtr = operation;
              operation->setChildLeft(new AlgebraicTreeOperation());
              length += _parse(expression+1, operation->getChildLeftPtr());
              operation->setChildRight(new AlgebraicTreeOperation());
              length += _parse(expression+start+1,operation->getChildRightPtr());
              while(isspace(*(expression+length))) length++;
              if(*(expression+length) != ')') return length-1;
              else{
                  while(*(expression+length)==')') length++;
              }
              return length;
          }
      }else{
          AlgebraicTreeNumber* number = new AlgebraicTreeNumber();
          char* endPtr;
          double value = strtod(expression, &endPtr);
          unsigned strLen = endPtr-expression;
          if(strLen==0||!(*(endPtr)=='*'||*(endPtr)=='+'||*(endPtr)=='-'||*(endPtr)=='/'||*(endPtr)==')'||*(endPtr)=='(')){
              number->setInvalid(true);
              number->setValue(0);
              return 0;
          }else{
              number->setValue(value);
              *nodePtr = number;
              length+= strLen;
              unsigned endLen = string(endPtr).length();
              unsigned i = 0;
              while(i<endLen){
                  if(*(expression+i)==')' || isspace(*(expression+i))) length++;
                  i++;
              }
              return length;
          }
      }
//  }
  return length;
}


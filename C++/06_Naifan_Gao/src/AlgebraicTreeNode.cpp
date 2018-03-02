#include <stdio.h>
#include <stdlib.h>
#include "AlgebraicTreeNode.hpp"

unsigned _ftoa(const double value, char* str) {
    static char buff[FTOA_BUFFER_LENGTH] = "";
    // memset(buff,'\0',FTOA_BUFFER_LENGTH*sizeof(char));
    unsigned length =
    (str!=(char*)0)?
    sprintf(str,FTOA_FORMAT,value):
    sprintf(buff,FTOA_FORMAT,value);
    return length;
}

AlgebraicTreeNode::~AlgebraicTreeNode() {
  // TBD
    if(!this->isInvalid()){
        delete this->_childLeft;
        delete this->_childRight;
    }
}

AlgebraicTreeNode::AlgebraicTreeNode() {
  // TBD
    _parent=(AlgebraicTreeNode*)0;
    _childLeft =(AlgebraicTreeNode*)0;
    _childRight=(AlgebraicTreeNode*)0;
    _type=INVALID;
    _value=0.0;
}

AlgebraicTreeNode::AlgebraicTreeNode(const double value) {
  // TBD
    _parent = (AlgebraicTreeNode*)0;
    _childLeft = (AlgebraicTreeNode*)0;
    _childRight = (AlgebraicTreeNode*)0;
    _type=NUMBER;
    _value = value;
}

AlgebraicTreeNode::AlgebraicTreeNode(const AlgebraicTreeNodeType type) {
  // TBD
    _parent = (AlgebraicTreeNode*)0;
    _childLeft = (AlgebraicTreeNode*)0;
    _childRight = (AlgebraicTreeNode*)0;
    _type=type;
    _value = 0.0;
}
AlgebraicTreeNode::AlgebraicTreeNode(AlgebraicTreeNode&src){
    if(src._childLeft == NULL ||src._childRight==NULL || src.isInvalid()){
        _parent=(AlgebraicTreeNode*)0;
        _childLeft =(AlgebraicTreeNode*)0;
        _childRight=(AlgebraicTreeNode*)0;
        _type=INVALID;
        _value=0.0;
    }else{
        this->_type = src._type;
        this->_value = src._value;
        this->_childLeft = copyTree(src._childLeft);
        this->_childRight = copyTree(src._childRight);
    }
}

AlgebraicTreeNode* AlgebraicTreeNode::copyTree(AlgebraicTreeNode*& oldNode){
    AlgebraicTreeNode* node = new AlgebraicTreeNode();
    if(oldNode==(AlgebraicTreeNode*)NULL){
        node->_parent = (AlgebraicTreeNode*)0;
        node->_childLeft = (AlgebraicTreeNode*)0;
        node->_childRight = (AlgebraicTreeNode*)0;
        node->_type=INVALID;
        node->_value = 0.0;
    }else{
        node->_value = oldNode->_value;
        node->_type = oldNode->_type;
        node->_parent = copyTree(oldNode->_parent);
        node->_childLeft = copyTree(oldNode->_childLeft);
        node->_childRight = copyTree(oldNode->_childRight);
    }
    return node;
}

void AlgebraicTreeNode::setParent(AlgebraicTreeNode* parent) {
  // TBD
    this->_parent= parent;
}

void AlgebraicTreeNode::setChildLeft(AlgebraicTreeNode* childLeft) {
  // TBD
    this->_childLeft = childLeft;
}

void AlgebraicTreeNode::setChildRight(AlgebraicTreeNode* childRight) {
  // TBD
    this->_childRight=childRight;
}

double AlgebraicTreeNode::evaluate() const {
  double value = 0.0f;
  // TBD
    if(!this->isInvalid()){
        if (this->isNumber()){
            return this->_value;
        }else if(this->isOperation()){
            if(this->_type==ADD)
                value += this->_childLeft->evaluate() + this->_childRight->evaluate();
            if(this->_type==SUBTRACT)
                value += this->_childLeft->evaluate() - this->_childRight->evaluate();
            if(this->_type==MULTIPLY)
                value += this->_childLeft->evaluate() * this->_childRight->evaluate();
            if(this->_type==DIVIDE)
                value += this->_childLeft->evaluate() / this->_childRight->evaluate();
        }
    }
  return value;
}

const bool AlgebraicTreeNode::isInvalid() const {
    if(this->_type==INVALID) return true;
  return false; // TBD : return true only if _type==INVALID
}

const bool AlgebraicTreeNode::isNumber() const {
    if(this->_type==NUMBER) return true;
  else return false; // TBD : return true only if _type==NUMBER
}

const bool AlgebraicTreeNode::isOperation() const {
    if(this->_type==ADD||this->_type==SUBTRACT||this->_type==DIVIDE||this->_type==MULTIPLY) return true;
  return false; // TBD : return true only if _type==???
}

const bool AlgebraicTreeNode::isRoot() const {
    if(this->_parent==NULL) return true;
  return false; // TBD
}
const bool AlgebraicTreeNode::isLeftChild() const {
    if(this->_parent->_childLeft==this) return true;
  return false; // TBD
}

const bool AlgebraicTreeNode::isRightChild() const {
    if(this->_parent->_childRight==this) return true;
  return false; // TBD
}

char* AlgebraicTreeNode::toString() const {
    // TBD
    unsigned N = this->_toStringLength();
    char* str = new char[N];
    memset(str,'\0',N*sizeof(char));
    _toString(str);
    return str;
}
unsigned AlgebraicTreeNode::_toStringLength() const{
    int len = 0;
    char stack[1024];
    if(!this->isInvalid()){
        if(this->isOperation()){
            len+=3;
            len += this->_childLeft->_toStringLength();
            len += this->_childRight->_toStringLength();
        }
        if(this->isNumber()){
            unsigned n = _ftoa(this->_value, stack);
            return n;
        }
        return len;
    }else{
        return 1024;
    }
}
unsigned AlgebraicTreeNode::_toString(char* str) const{
    int counts = 0;
    if(!this->isInvalid()){
        if(this->isNumber()){
            unsigned n = _ftoa(this->_value, str+counts);
            return n;
        }
        if(this->isOperation()){
            *(str+counts) = '(';
            counts++;
            counts += this->_childLeft->_toString(str+counts);
            if(this->_type==ADD) *(str+counts) = '+';
            if(this->_type==SUBTRACT) *(str+counts) = '-';
            if(this->_type==MULTIPLY) *(str+counts) = '*';
            if(this->_type==DIVIDE) *(str+counts) = '/';
            counts++;
            counts += this->_childRight->_toString(str+counts);
            *(str+counts) = ')';
            counts++;
            return counts;
        }
    }else{
        return 0;
    }
}

// new parser constructor
AlgebraicTreeNode::AlgebraicTreeNode(const char* expression) {
  // TBD
    this->_parent = (AlgebraicTreeNode*)0;
    this->_type = INVALID;
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
    length += _parseExpression(expression+length);
    if(length < strLength || parenthese != 0){
        this->_parent = (AlgebraicTreeNode*)0;
        this->_childLeft =(AlgebraicTreeNode*)0;
        this->_childRight=(AlgebraicTreeNode*)0;
        this->_type=INVALID;
        this->_value=0.0;
    }
}

// returns length of parsed substring 
unsigned AlgebraicTreeNode::_parseExpression(const char* expression) {
  unsigned length = 0;
  // TBD
    unsigned strlen = 0;
    unsigned len = string(expression).length();
    while(isspace(*(expression+length))) length++;
    strlen = length;
    if(*(expression+strlen) == '('){
        while(isspace(*(expression+strlen+1))) strlen++;
        if(*(expression+strlen+1) == '('){
            int parentheses = 0;
            bool isOperator = false;
            while(!isOperator){
                strlen++;
                if(*(expression+strlen) == '(') parentheses++;
                else if(*(expression+strlen)== ')') parentheses--;
                if(parentheses==0) isOperator=true;
            }
            if(strlen >= len) return 0;
            else{
                strlen++;
                while(isspace(*(expression+strlen))){
                    strlen++;
                }
                if(*(expression+strlen)=='+') this->_type=ADD;
                if(*(expression+strlen)=='-') this->_type=SUBTRACT;
                if(*(expression+strlen)=='*') this->_type= MULTIPLY;
                if(*(expression+strlen)=='/') this->_type=DIVIDE;
                this->_childLeft = new AlgebraicTreeNode();
                unsigned cl = this->_childLeft->_parseExpression(expression+1);
                if(this->_childLeft->_type==INVALID && this->_childLeft->_childLeft==(AlgebraicTreeNode*)0 && this->_childLeft->_childRight==(AlgebraicTreeNode*)0){
                    this->_childRight = new AlgebraicTreeNode();
                    delete this;
                    return 0;
                }
                this->_childRight = new AlgebraicTreeNode();
                unsigned cr = this->_childRight->_parseExpression(expression+strlen+1);
                if(this->_childRight->_type==INVALID && this->_childRight->_childLeft==(AlgebraicTreeNode*)0 && this->_childRight->_childRight==(AlgebraicTreeNode*)0){
                    delete this;
                    return 0;
                }
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
            if(*(expression+start)=='+') this->_type=ADD;
            if(*(expression+start)=='-') this->_type=SUBTRACT;
            if(*(expression+start)=='*') this->_type= MULTIPLY;
            if(*(expression+start)=='/') this->_type=DIVIDE;
            length += 2;
            this->_childLeft = new AlgebraicTreeNode();
            length += this->_childLeft->_parseExpression(expression+space+1);
            if(this->_childLeft->_type==INVALID && this->_childLeft->_childLeft==(AlgebraicTreeNode*)0 && this->_childLeft->_childRight==(AlgebraicTreeNode*)0){
                this->_childRight = new AlgebraicTreeNode();
                delete this;
                return 0;
            }
            this->_childRight = new AlgebraicTreeNode();
            length += this->_childRight->_parseExpression(expression+start+1);
            if(this->_childRight->_type==INVALID && this->_childRight->_childLeft==(AlgebraicTreeNode*)0 && this->_childRight->_childRight==(AlgebraicTreeNode*)0){
                delete this;
                return 0;
            }
            while(isspace(*(expression+length))) length++;
            if(*(expression+length) != ')') return length-1;
            else{
                while(*(expression+length)==')') length++;
            }
            return length;
        }
    }else{
        this->_type = NUMBER;
        unsigned value = _parseNumber(expression);
        if(value==0) return 0;
        return length+value;
    }
    return length;
}

unsigned AlgebraicTreeNode::_parseNumber(const char* expression) {
  unsigned length = 0;
  // TBD
    char* endPtr;
    double value = strtod(expression, &endPtr);
    unsigned strLen = endPtr-expression;
    if(strLen==0||!(*(endPtr)=='*'||*(endPtr)=='+'||*(endPtr)=='-'||*(endPtr)=='/'||*(endPtr)==')'||*(endPtr)=='(')){
        this->_type=INVALID;
        this->_value = 0;
        return 0;
    }else{
        this->_value=value;
        this->_childLeft = (AlgebraicTreeNode*)0;
        this->_childRight = (AlgebraicTreeNode*)0;
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

// HINT:
// implement these private methods and use them in the
// implementation of some of the public methods defined above
// 
// It will be OK to design your implementation withou implementing
// these methods
//
// unsigned AlgebraicTreeNode::_toStringLength() const {
//   unsigned length = 0;
//   // TBD
//   return length;
// }
//
// unsigned AlgebraicTreeNode::_toString(char* str) const {
//   unsigned length = 0;
//   // TBD
//   return length;
// }
//



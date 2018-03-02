#include <stdlib.h>
#include <string.h>
#include "AlgebraicTreeExpression.hpp"

AlgebraicTreeExpression::~AlgebraicTreeExpression() {
    delete this->_root;
    // TBD
}

AlgebraicTreeExpression::AlgebraicTreeExpression() {
  // TBD
    _root = (AlgebraicTreeNode*)0;
}

bool AlgebraicTreeExpression::isEmpty() const {
    if(this->_root->isInvalid()) return true;
  return false; // TBD
}

double AlgebraicTreeExpression::evaluate() const {
    if(this->_root->isNumber()) return this->_root->evaluate();
    if(this->_root->isOperation()) return this->_root->evaluate();
    if(this->_root->isUnary()) return this->_root->evaluate();
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
        delete this->_root;
        AlgebraicTreeOperation* root = new AlgebraicTreeOperation();
        root->setInvalid(true);
        this->setRoot(root);
    }
}

unsigned AlgebraicTreeExpression::_parse
(const char* expression, AlgebraicTreeNode** nodePtr, bool operand) {
  unsigned length = 0;
  char*    ptr = (char*)expression;
  bool     onlyCheckSyntax = (*nodePtr==(AlgebraicTreeNode*)0);
    unsigned strlen = 0;
    unsigned label = 0;
    unsigned len = string(ptr).length();
    while(isspace(*(ptr+length))) length++;
    strlen = length;
    if(*(ptr+strlen) == '('){
        while(isspace(*(ptr+strlen+1))) strlen++;
        if(*(ptr+strlen+1) == '('||*(ptr+strlen+1)=='c'||*(ptr+strlen+1)=='s'||*(ptr+strlen+1)=='t'){
            int parentheses = 0;
            bool isOperator = false;
            if(*(ptr+strlen+1) == '('){
                while(!isOperator && strlen < len){
                    strlen++;
                    if(*(ptr+strlen) == '(') parentheses++;
                    else if(*(ptr+strlen)== ')') parentheses--;
                    if(parentheses==0) isOperator=true;
                }
            }else{
                while(*(ptr+strlen)!=')' && (*(ptr+strlen+1)!='+'||*(ptr+strlen+1)!='-'||*(ptr+strlen+1)!='*'||*(ptr+strlen+1)!='/'))
                    strlen++;
                while(*(ptr+strlen+1)==')') strlen++;
                if(strlen==len-1 && operand==true){
                    length++;
                    length += _parse(ptr+1, nodePtr);
                    return length;
                }
            }
            if(strlen >= len) return 0;
            else{
                strlen++;
                while(isspace(*(ptr+strlen))){
                    strlen++;
                }
                label = strlen;
            }
        }else{
            int space = length;
            while(isspace(*(ptr+length))){
                length++;
                space++;
            }
            unsigned start = 1;
            bool isNumber = false;
            do{
                start++;
                if(start > string(ptr).length()|| *(ptr+start)==')') {
                    if(operand){
                        isNumber=true;
                        break;
                    }else return 0;
                }
                if(*(ptr+start-1)=='e') start += 1;
                if(isspace(*(ptr+start))) length++;
            }while(*(ptr+start)!='+' && *(ptr+start)!='-' && *(ptr+start)!='*' && *(ptr+start)!='/');
            if(isNumber){
                length += _parse(ptr+1, nodePtr);
                return length;
            }
            else label = start;
            }
            AlgebraicTreeOperation* operation =new AlgebraicTreeOperation();
            if(*(expression+label)=='+') operation->setType(ADD);
            else if(*(expression+label)=='-') operation->setType(SUBTRACT);
            else if(*(expression+label)=='*') operation->setType(MULTIPLY);
            else if(*(expression+label)=='/') operation->setType(DIVIDE);
            else return 0;  // how to deal with (7*5) and the difference between sqrt(7*5)
            if(onlyCheckSyntax==true) setRoot(operation);
            else *nodePtr = operation;
            operation->setChildLeft(new AlgebraicTreeOperation());
            unsigned cl = _parse(ptr+1, operation->getChildLeftPtr());
            operation->setChildRight(new AlgebraicTreeOperation());
            unsigned cr = _parse(ptr+label+1,operation->getChildRightPtr());
            length += 2 + cl + cr;
            if(*(expression+length) != ')') return length-1;
            else{
                while(*(expression+length)==')') length++;
            }
            while(*(expression+length)==')') length++;
            return length;
    }else if(*(ptr+strlen) == 'c'||*(ptr+strlen)=='s'||*(ptr+strlen)=='t'){
        string str = string(ptr+length);
        string substr;
        int offset = 0;
        if(*(ptr+strlen+1) == 'q'){
            substr = str.substr(0, 4);
            offset = 4;
        }
        else{
            substr = str.substr(0,3);
            offset = 3;
        }
        length += offset+1;
        AlgebraicTreeUnary* unary = new AlgebraicTreeUnary();
        if(substr=="cos") unary->setType(COS);
        else if(substr=="sin") unary->setType(SIN);
        else if(substr=="sqrt") unary->setType(SQRT);
        else if(substr=="tan") unary->setType(TAN);
        else return 0;
        if(onlyCheckSyntax==true) setRoot(unary);
        else *nodePtr = unary;
        unary->setChild(new AlgebraicTreeOperation());
        unsigned child = _parse(ptr+offset, unary->getChildPtr(), true);
        length += child;
        if(*(expression+length) != ')') return length-1;
        else{
            while(*(expression+length)==')') length++;
        }
        while(*(expression+length)==')') length++;
        return length;
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
    return length;
}


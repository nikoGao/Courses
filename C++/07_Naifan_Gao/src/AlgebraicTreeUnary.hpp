//
//  AlgebraicTreeUnary.hpp
//  Calc7
//
//  Created by Niko Gao on 10/13/17.
//

#ifndef AlgebraicTreeUnary_h
#define AlgebraicTreeUnary_h

#include <cmath>
#include "AlgebraicTreeNode.hpp"
#define PI 3.14159265

enum AlgebraicUnaryOperator {
    SIN, COS, SQRT, TAN, NONE
};

class AlgebraicTreeUnary : public AlgebraicTreeNode{
    
public:
    virtual ~AlgebraicTreeUnary();
    AlgebraicTreeUnary(AlgebraicUnaryOperator operand=NONE);
    virtual const bool isNumber() const;
    virtual const bool isOperation() const;
    virtual const bool isUnary() const;
    
    virtual double     evaluate() const;
    virtual unsigned   toStringLength() const;
    virtual unsigned   toString(char& str) const;
    
    void setType(AlgebraicUnaryOperator operand);
    void setChild(AlgebraicTreeNode* child);
    
    AlgebraicTreeNode* getChild();
    AlgebraicTreeNode** getChildPtr();
    
private:
    AlgebraicUnaryOperator _operand;
    AlgebraicTreeNode* _child;
};

#endif /* AlgebraicTreeUnary_h */

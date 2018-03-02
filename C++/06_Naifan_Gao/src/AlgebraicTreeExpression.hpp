#ifndef _AlgebraicTreeExpression_hpp_
#define _AlgebraicTreeExpression_hpp_

#include "AlgebraicTreeNode.hpp"

class AlgebraicTreeExpression {

public:

  ~AlgebraicTreeExpression();

  AlgebraicTreeExpression();
  AlgebraicTreeExpression(const char* expression);

  // copy constructor
  AlgebraicTreeExpression(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& operator=(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& swap(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& operator+=(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& operator-=(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& operator*=(AlgebraicTreeExpression& src);
  AlgebraicTreeExpression& operator/=(AlgebraicTreeExpression& src);

  double evaluate() const;
  char*  toString() const;

private:

  AlgebraicTreeExpression& _operatorInPlace(AlgebraicTreeNodeType type,AlgebraicTreeExpression& src);

protected:

  AlgebraicTreeNode* _root;

};

#endif // _AlgebraicTreeExpression_hpp_

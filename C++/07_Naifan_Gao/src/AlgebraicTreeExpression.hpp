#ifndef _AlgebraicTreeExpression_hpp_
#define _AlgebraicTreeExpression_hpp_

#include "AlgebraicTreeNode.hpp"
#include "AlgebraicTreeNumber.hpp"
#include "AlgebraicTreeOperation.hpp"
#include "AlgebraicTreeUnary.hpp"
#include <string>
using namespace std;
class AlgebraicTreeExpression {

public:

  ~AlgebraicTreeExpression();

  AlgebraicTreeExpression();
  AlgebraicTreeExpression(const char* expression);

  bool   isEmpty() const;
  double evaluate() const;
  char*  toString() const;

  void setRoot(AlgebraicTreeNode* root);

protected:

   AlgebraicTreeNode* _root;

  unsigned _parse(const char* expression, AlgebraicTreeNode** parentPtr, bool operand=false);

};

#endif // _AlgebraicTreeExpression_hpp_

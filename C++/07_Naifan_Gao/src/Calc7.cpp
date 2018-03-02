//
//  Calc6b.cpp
//
//  Created by Gabriel Taubin on 10/02/2015.
//  Copyright (c) 2015 Gabriel Taubin. All rights reserved.
//

#include <iostream>

#include "AlgebraicTreeExpression.hpp"

using namespace std;

const char* expr1str = "(7+cos(8))";

// AlgebraicTreeExpression* newExpr1() {
//     AlgebraicTreeExpression* expr = new AlgebraicTreeExpression();
//     AlgebraicTreeOperation* root =
//       new AlgebraicTreeOperation(ADD);
//     expr->setRoot(root);
//     {
//         root->setChildLeft(new AlgebraicTreeNumber(7));
//         AlgebraicTreeUnary* child = new AlgebraicTreeUnary(COS);
//         root->setChildRight(child);
//         AlgebraicTreeOperation* child_child = new AlgebraicTreeOperation(MULTIPLY);
//         child->setChild(child_child);
//       child_child->setChildLeft(new AlgebraicTreeNumber(8.0));
//       child_child->setChildRight(new AlgebraicTreeNumber(5.0));
//     }
//     return expr;
// }

const char* expr2str = "(7+(8*5))";

// AlgebraicTreeExpression* newExpr2() {
//     AlgebraicTreeExpression* expr = new AlgebraicTreeExpression();
//     AlgebraicTreeOperation* node0 =
//       new AlgebraicTreeOperation(ADD);
//     expr->setRoot(node0);
//     {
//       node0->setChildLeft(new AlgebraicTreeNumber(7.0));
//       AlgebraicTreeOperation* node1 =
//         new AlgebraicTreeOperation(MULTIPLY);
//       node0->setChildRight(node1);
//       {
//         node1->setChildLeft(new AlgebraicTreeNumber(8.0));
//         node1->setChildRight(new AlgebraicTreeNumber(5.0));
//       }
//     }
//     return expr;
// }

const char* expr3str = "(((3*5)+(4*(7+(8*5))))*(7-(9*3)))";

// AlgebraicTreeExpression* newExpr3() {
//   AlgebraicTreeExpression* expr = new AlgebraicTreeExpression();
//   // "(((3*5)+(4*(7+(8*5))))*(7-(9*3)))"
//   AlgebraicTreeOperation* node0 = new AlgebraicTreeOperation(MULTIPLY);
//   expr->setRoot(node0);
//   {
//     // ((3*5)+(4*(7+(8*5))))
//     AlgebraicTreeOperation* node1 =
//       new AlgebraicTreeOperation(ADD);
//     node0->setChildLeft(node1);
//     {
//       // (3*5)
//       AlgebraicTreeOperation* node2 =
//         new AlgebraicTreeOperation(MULTIPLY);
//       node1->setChildLeft(node2);
//       {
//         node2->setChildLeft(new AlgebraicTreeNumber(3.0));
//         node2->setChildRight(new AlgebraicTreeNumber(5.0));
//       }
//       // (4*(7+(8*5)))
//       AlgebraicTreeOperation* node3 =
//         new AlgebraicTreeOperation(MULTIPLY);
//       node1->setChildRight(node3);
//       {
//         node3->setChildLeft(new AlgebraicTreeNumber(4.0));
//         // (7+(8*5))
//         AlgebraicTreeOperation* node4 =
//           new AlgebraicTreeOperation(ADD);
//         node3->setChildRight(node4);
//         {
//           node4->setChildLeft(new AlgebraicTreeNumber(7.0));
//           // (8*5)
//           AlgebraicTreeOperation* node5 =
//             new AlgebraicTreeOperation(MULTIPLY);
//           node4->setChildRight(node5);
//           {
//             node5->setChildLeft(new AlgebraicTreeNumber(8.0));
//             node5->setChildRight(new AlgebraicTreeNumber(5.0));
//           }
//         }
//       }
//     }
//     // (7-(9*3))
//     AlgebraicTreeOperation* node6 =
//       new AlgebraicTreeOperation(SUBTRACT);
//     node0->setChildRight(node6);
//     {
//       node6->setChildLeft(new AlgebraicTreeNumber(7.0));
//       AlgebraicTreeOperation* node7 =
//         new AlgebraicTreeOperation(MULTIPLY);
//       node6->setChildRight(node7);
//       {
//         node7->setChildLeft(new AlgebraicTreeNumber(9.0));
//         node7->setChildRight(new AlgebraicTreeNumber(3.0));
//       }
//     }
//   }
//   return expr;
// }

const char* expr4str =
  "(((3.1*-5.35)+(4.1e-2*(-7.0e+1+(0.08*5.0e-3))))*(7-(9.0*-0.23)))";

const char* expr5str = "(((cos(3.1)*-5.35)+(4.1e-2*(-7.0e+1+sqrt(0.08*5.0e-3))))*(tan(7)-sin(9.0*-0.23)))";
const char* expr6str = "cos((sqrt(0.35)*0.4)+sin(tan(0.45)))";

//////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {

//   AlgebraicTreeExpression* expr = newExpr1();
  // AlgebraicTreeExpression* expr = newExpr2();
//   AlgebraicTreeExpression* expr = newExpr3();

//   const char* exprStr = expr1str;
  // const char* exprStr = expr2str;
//   const char* exprStr = expr3str;
//  const char* exprStr = expr4str;
    const char* exprStr = expr5str;
//    const char* exprStr = expr6str;

  AlgebraicTreeExpression* expr = new AlgebraicTreeExpression(exprStr);

  cout << "input  = \"" << exprStr << "\"" << endl;

  if(expr->isEmpty()) {
    cout << "\"" << "expression is empty" << endl;
    return -2;
  }

  char*  outStr = expr->toString();
  double value = expr->evaluate();

  cout << "parsed = \"" << outStr  << "\" = " << value << endl;

  delete [] outStr;
  delete expr;

  return 0;
}

//
//  Calc5.cpp
//
//  Created by Gabriel Taubin on 9/27/17
//  Copyright (c) 2017 Gabriel Taubin. All rights reserved.
//

#include <iostream>

#include "AlgebraicTreeNode.hpp"

using namespace std;

AlgebraicTreeNode* newExpr1() {
    AlgebraicTreeNode* root = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    AlgebraicTreeNode* rootLeft = new AlgebraicTreeNode(8);
    AlgebraicTreeNode* rootRight = new AlgebraicTreeNode(5);
    root->setChildLeft(rootLeft);
    root->setChildRight(rootRight);
  // construct data structure for expression “(8*5)"
    cout << "node" << root->getId() << ":" << root->toString() << "= " << root->evaluate()<<endl;
    cout << "node" << rootLeft->getId() << ":" << rootLeft->toString() << "= " << rootLeft->evaluate()<<endl;
    cout << "node" << rootRight->getId() << ":" << rootRight->toString() << "= " << rootRight->evaluate()<<endl;
  return root;
}

AlgebraicTreeNode* newExpr2() {
    int i = 0;
    AlgebraicTreeNode* root = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    AlgebraicTreeNode* rootLeft = new AlgebraicTreeNode(4);
    root->setChildLeft(rootLeft);
    root->setId(i);
    i++;
    rootLeft->setParent(root);
    rootLeft->setId(i);
    i++;
    AlgebraicTreeNode* rootRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::ADD);
    rootRight->setId(i++);
    root->setChildRight(rootRight);
    rootRight->setParent(root);
    AlgebraicTreeNode* childLeft = new AlgebraicTreeNode(7);
    childLeft->setId(i++);
    AlgebraicTreeNode* childRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    childRight->setId(i++);
    rootRight->setChildLeft(childLeft);
    childLeft->setParent(rootRight);
    rootRight->setChildRight(childRight);
    childRight->setParent(rootRight);
    AlgebraicTreeNode* secondChildLeft = new AlgebraicTreeNode(8);
    secondChildLeft->setId(i++);
    childRight->setChildLeft(secondChildLeft);
    secondChildLeft->setParent(childRight);
    AlgebraicTreeNode* secondChildRight = new AlgebraicTreeNode(5);
    secondChildRight->setId(i++);
    childRight->setChildRight(secondChildRight);
    secondChildRight->setParent(childRight);
//   construct data structure for expression “(4*((8*5)+7))"
    cout << "node" << root->getId() << ":" << root->toString() << "= " << root->evaluate()<<endl;
    cout << "node" << rootLeft->getId() << ":" << rootLeft->toString() << "= " << rootLeft->evaluate()<<endl;
    cout << "node" << rootRight->getId() << ":" << rootRight->toString() << "= " << rootRight->evaluate()<<endl;
    cout << "node" << childLeft->getId() << ":" << childLeft->toString() << "= " << childLeft->evaluate()<<endl;
    cout << "node" << childRight->getId() << ":" << childRight->toString() << "= " << childRight->evaluate()<<endl;
    cout << "node" << secondChildLeft->getId() << ":" << secondChildLeft->toString() << "= " << secondChildLeft->evaluate()<<endl;
    cout << "node" << secondChildRight->getId() << ":" << secondChildRight->toString() << "= " << secondChildRight->evaluate()<<endl;
  return root;
}

AlgebraicTreeNode* newExpr3() {
    int i= 0;
    AlgebraicTreeNode* root = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    root->setId(i++);
    AlgebraicTreeNode* rootLeft = new AlgebraicTreeNode(AlgebraicTreeNodeType::ADD);
    rootLeft->setId(i++);
    AlgebraicTreeNode* rootRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::SUBTRACT);
    rootRight->setId(i++);
    root->setChildLeft(rootLeft);
    root->setChildRight(rootRight);
    AlgebraicTreeNode* secondLeft = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    secondLeft->setId(i++);
    AlgebraicTreeNode* secondRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    secondRight->setId(i++);
    rootLeft->setChildLeft(secondLeft);
    rootLeft->setChildRight(secondRight);
    AlgebraicTreeNode* secondLeftR = new AlgebraicTreeNode(7);
    secondLeftR->setId(i++);
    AlgebraicTreeNode* secondRightR = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    secondRightR->setId(i++);
    rootRight->setChildLeft(secondLeftR);
    rootRight->setChildRight(secondRightR);
    AlgebraicTreeNode* thirdRLeft = new AlgebraicTreeNode(9);
    thirdRLeft->setId(i++);
    secondRightR->setChildLeft(thirdRLeft);
    AlgebraicTreeNode* thirdRRight = new AlgebraicTreeNode(3);
    thirdRRight->setId(i++);
    secondRightR->setChildRight(thirdRRight);
    AlgebraicTreeNode* thirdLLeft = new AlgebraicTreeNode(3);
    thirdLLeft->setId(i++);
    secondLeft->setChildLeft(thirdLLeft);
    AlgebraicTreeNode* thirdLRight = new AlgebraicTreeNode(5);
    thirdLRight->setId(i++);
    secondLeft->setChildRight(thirdLRight);
    AlgebraicTreeNode* thirdLeft = new AlgebraicTreeNode(4);
    thirdLeft->setId(i++);
    secondRight->setChildLeft(thirdLeft);
    AlgebraicTreeNode* thirdRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::ADD);
    thirdRight->setId(i++);
    secondRight->setChildRight(thirdRight);
    AlgebraicTreeNode* fourthLeft = new AlgebraicTreeNode(7);
    fourthLeft->setId(i++);
    thirdRight->setChildLeft(fourthLeft);
    AlgebraicTreeNode* fourthRight = new AlgebraicTreeNode(AlgebraicTreeNodeType::MULTIPLY);
    fourthRight->setId(i++);
    thirdRight->setChildRight(fourthRight);
    AlgebraicTreeNode* fifthLeft = new AlgebraicTreeNode(8);
    fifthLeft->setId(i++);
    fourthRight->setChildLeft(fifthLeft);
    AlgebraicTreeNode* fifthRight = new AlgebraicTreeNode(5);
    fifthRight->setId(i++);
    fourthRight->setChildRight(fifthRight);
    cout << "node" << root->getId() << ":" << root->toString() << "= " << root->evaluate()<<endl;
    cout << "node" << rootLeft->getId() << ":" << rootLeft->toString() << "= " << rootLeft->evaluate()<<endl;
    cout << "node" << rootRight->getId() << ":" << rootRight->toString() << "= " << rootRight->evaluate()<<endl;
    cout << "node" << secondLeft->getId() << ":" << secondLeft->toString() << "= " << secondLeft->evaluate()<<endl;
    cout << "node" << secondRight->getId() << ":" << secondRight->toString() << "= " << secondRight->evaluate()<<endl;
    cout << "node" << secondLeftR->getId() << ":" << secondLeftR->toString() << "= " << secondLeftR->evaluate()<<endl;
    cout << "node" << secondRightR->getId() << ":" << secondRightR->toString() << "= " << secondRightR->evaluate()<<endl;
    cout << "node" << thirdRLeft->getId() << ":" << thirdRLeft->toString() << "= " << thirdRLeft->evaluate()<<endl;
    cout << "node" << thirdRRight->getId() << ":" << thirdRRight->toString() << "= " << thirdRRight->evaluate()<<endl;
    cout << "node" << thirdLLeft->getId() << ":" << thirdLLeft->toString() << "= " << thirdLLeft->evaluate()<<endl;
    cout << "node" << thirdLRight->getId() << ":" << thirdLRight->toString() << "= " << thirdLRight->evaluate()<<endl;
    cout << "node" << thirdLeft->getId() << ":" << thirdLeft->toString() << "= " << thirdLeft->evaluate()<<endl;
    cout << "node" << thirdRight->getId() << ":" << thirdRight->toString() << "= " << thirdRight->evaluate()<<endl;
    cout << "node" << fourthLeft->getId() << ":" << fourthLeft->toString() << "= " << fourthLeft->evaluate()<<endl;
    cout << "node" << fourthRight->getId() << ":" << fourthRight->toString() << "= " << fourthRight->evaluate()<<endl;
    cout << "node" << fifthLeft->getId() << ":" << fifthLeft->toString() << "= " << fifthLeft->evaluate()<<endl;
    cout << "node" << fifthRight->getId() << ":" << fifthRight->toString() << "= " << fifthRight->evaluate()<<endl;
  // construct data structure for expression "(((3*5)+(4*(7+(8*5))))*(7-(9*3)))"
  return root;
}

int main(int argc, const char * argv[]) {

  //AlgebraicTreeNode* root = newExpr1();
  //AlgebraicTreeNode* root = newExpr2();
   AlgebraicTreeNode* root = newExpr3();

  if(root->isInvalid()) {
    cout << "expression is invalid" << endl;
    return -2;
  }

  char*  str   = root->toString();
  double value = root->evaluate();
  
  cout << "\"" << str << "\" = " << value << endl;
  delete [] str;
  delete root;
  return 0;
}

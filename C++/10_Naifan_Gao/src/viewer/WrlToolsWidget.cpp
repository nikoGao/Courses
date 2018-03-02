//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-05 22:46:31 taubin>
//------------------------------------------------------------------------
//
// WrlToolsWidget.cpp
//
// Software developed for the Fall 2017 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2017, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <iostream>
#include "WrlToolsWidget.hpp"
#include "WrlMainWindow.hpp"

WrlToolsWidget::WrlToolsWidget(WrlMainWindow *mw):
  QWidget(),
  _mainWindow(mw) {

  static const char* bg0 =
    "QLabel { background-color : rgb(200,200,200); color : black; }";

  QFont font;
  font.setPointSize(10);

  _label3DCanvas = new QLabel(this);
  _label3DCanvas->setText("3D CANVAS");
  _label3DCanvas->setAlignment(Qt::AlignCenter);
  _label3DCanvas->setStyleSheet(bg0);
  _label3DCanvas->setFont(font);

  _label3DCanvasWidth = new QLabel(this);
  _label3DCanvasWidth->setText("WIDTH");
  _label3DCanvasWidth->setAlignment(Qt::AlignCenter);
  _label3DCanvasWidth->setFont(font);

  _edit3DCanvasWidth = new QLineEdit(this);
  _edit3DCanvasWidth->setFont(font);
  _edit3DCanvasWidth->setReadOnly(true);

  _label3DCanvasHeight = new QLabel(this);
  _label3DCanvasHeight->setText("HEIGHT");
  _label3DCanvasHeight->setAlignment(Qt::AlignCenter);
  _label3DCanvasHeight->setFont(font);

  _edit3DCanvasHeight = new QLineEdit(this);
  _edit3DCanvasHeight->setFont(font);
  _edit3DCanvasHeight->setReadOnly(true);
}

WrlToolsWidget::~WrlToolsWidget() {
}

void WrlToolsWidget::updateState() {
  _edit3DCanvasWidth->setText
    (QString::number(_mainWindow->getGLWidgetWidth()));
  _edit3DCanvasHeight->setText
    (QString::number(_mainWindow->getGLWidgetHeight()));
}

void WrlToolsWidget::resizeEvent(QResizeEvent * event) {

  int width  = event->size().width();
  // int height = event->size().height();

  int rowH = 20;
  int rowBorder = 0;
  int colBorder = 0;
  int rowSpace = 3;
  int colSpace = 3;

  int x,y,w,x0,x1,x2,x3,w0,w1,w2,w3;

  x = colBorder;
  w = width-2*colBorder;
  y = rowBorder;

  _label3DCanvas->setFixedHeight(rowH);
  _label3DCanvas->setGeometry(x,y,w,rowH);

  y += rowH+rowSpace;

  w0 = (width-3*colSpace-2*colBorder)/4;
  w1 = w0;
  w2 = w1;
  w3 = width-3*colSpace-2*colBorder-w0-w1-w2;
  x0 = colBorder;
  x1 = x0+w0+colSpace;
  x2 = x1+w1+colSpace;
  x3 = x2+w2+colSpace;

  _label3DCanvasWidth->setFixedHeight(rowH);
  _label3DCanvasWidth->setGeometry(x0,y,w0,rowH);
  _edit3DCanvasWidth->setFixedHeight(rowH);
  _edit3DCanvasWidth->setGeometry(x1,y,w1,rowH);
  _label3DCanvasHeight->setFixedHeight(rowH);
  _label3DCanvasHeight->setGeometry(x2,y,w2,rowH);
  _edit3DCanvasHeight->setFixedHeight(rowH);
  _edit3DCanvasHeight->setGeometry(x3,y,w3,rowH);
}

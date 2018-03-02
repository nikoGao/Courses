//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:17:27 taubin>
//------------------------------------------------------------------------
//
// WrlViewerApp.cpp
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

// #include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "WrlMainWindow.hpp"

int main( int argc, char ** argv ) {
  // cout << "WrlViewerApp::main() {\n";

  QApplication app( argc, argv );

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
    format.setSamples(4);

  // format.setRenderableType(QSurfaceFormat::OpenGLES);

  QSurfaceFormat::setDefaultFormat(format);

  // QSurfaceFormat::RenderableType rt = format.renderableType();
  // switch(rt) {
  // case QSurfaceFormat::DefaultRenderableType:
  //   cout << "  QSurfaceFormat::DefaultRenderableType\n";
  //   break;
  // case QSurfaceFormat::OpenGL:
  //   cout << "  QSurfaceFormat::OpenGL\n";
  //   break;
  // case QSurfaceFormat::OpenGLES:
  //   cout << "  QSurfaceFormat::OpenGLES\n";
  //   break;
  // case QSurfaceFormat::OpenVG:
  //   cout << "  QSurfaceFormat::OpenVG\n";
  //   break;
  // }

  // cout << "  creating WrlMainWindow ... \n";

  WrlMainWindow mw;

  // cout << "  resizing ... \n";

  mw.setMinimumSize(500,500);

  // cout << "  showing ... \n";

  mw.show();

  // cout << "  updating geometry ... \n";

  mw.updateGeometry();

  mw.setGLWidgetSize(600,600);


  // cout << "}\n";

  return app.exec();
}

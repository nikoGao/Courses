//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2015-11-01 01:33:43 taubin>
//------------------------------------------------------------------------
//
// IfsGLHandles.hpp
//
// Software developed for the Fall 2015 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2015, Gabriel Taubin
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

#ifndef IFS_GLHANDLES_HPP
#define IFS_GLHANDLES_HPP

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class IfsGLHandles {

public:

  IfsGLHandles();
  ~IfsGLHandles();

  void setColor(QColor& materialColor);
  void setGeometry(float hx0, float hy0, float hx1, float hy1);

  QMatrix4x4&          getMatrix();
  void                 paint(QOpenGLFunctions& f);

private:

  QOpenGLShader        *_vshader;
  QOpenGLShader        *_fshader;
  QOpenGLShaderProgram *_program;

  int                   _vertexAttr;
  int                   _matrixAttr ;
  int                   _materialAttr;

  QOpenGLBuffer         *_buffer;
  QColor                _materialColor;
  QMatrix4x4            _matrix;

};

#endif // IFS_GLHANDLES_HPP

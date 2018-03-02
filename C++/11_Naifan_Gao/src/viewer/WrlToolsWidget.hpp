//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:24:21 taubin>
//------------------------------------------------------------------------
//
// WrlToolsWidget.hpp
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

#ifndef _WRL_TOOLSWIDGET_HPP_
#define _WRL_TOOLSWIDGET_HPP_

#include <QResizeEvent>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>

class WrlMainWindow;

class WrlToolsWidget : public QWidget {

  Q_OBJECT

public:

  WrlToolsWidget(WrlMainWindow *mw);
  ~WrlToolsWidget();

public slots:
                   
  void updateState();

protected:

  // virtual void	enterEvent(QEvent * event)                 Q_DECL_OVERRIDE;
  // virtual void	leaveEvent(QEvent * event)                 Q_DECL_OVERRIDE;
  // virtual void	mousePressEvent(QMouseEvent * event)       Q_DECL_OVERRIDE;
  // virtual void	mouseReleaseEvent(QMouseEvent * event)     Q_DECL_OVERRIDE;
  // virtual void	mouseMoveEvent(QMouseEvent * event)        Q_DECL_OVERRIDE;

  virtual void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

private slots:

  // bounding box
  void bboxAdd();
  void bboxRemove();
  void bboxSetDepth(int depth);
  void bboxDepthUp();
  void bboxDepthDown();
  void bboxScaleEnter();
  void bboxCube();
  void bboxCubeSetState(int state);

  // scene graph
  void edgesAdd();
  void edgesRemove();
  void setNormalNone();
  void setNormalPerVertex();
  void setNormalPerFace();
  void setNormalPerCorner();
  void normalInvert();
  void shapeIfsShow();
  void shapeIfsHide();
  void shapeIlsShow();
  void shapeIlsHide();

  // points
  void pointsRemove();
  void pointsShow();
  void pointsHide();

  // surface reconstruction
  void surfaceRemove();
  void surfaceShow();
  void surfaceHide();
  void singlePlaneFit();
  void multiplePlanesFit();
  void continuousFit();

private:

  WrlMainWindow*        _mainWindow;

  QLabel*               _labelCanvas;
  QLabel*               _labelCanvasWidth;
  QLineEdit*            _editCanvasWidth;
  QLabel*               _labelCanvasHeight;
  QLineEdit*            _editCanvasHeight;

  QLabel*               _labelBBox;
  QLabel*               _labelBBoxSize;
  QSpinBox*             _spinBoxBBoxDepth;
  QPushButton*          _pushButtonBBoxAdd;
  QPushButton*          _pushButtonBBoxRemove;
  QLabel*               _labelBBoxScale;
  QLineEdit*            _editBBoxScale;
  QCheckBox*            _checkBoxBBoxCube;

  QLabel*               _labelSceneGraph;
  QLabel*               _labelSceneGraphNormalBinding;
  QPushButton*          _pushButtonSceneGraphNormalNone;
  QPushButton*          _pushButtonSceneGraphNormalPerVertex;
  QPushButton*          _pushButtonSceneGraphNormalPerFace;
  QPushButton*          _pushButtonSceneGraphNormalPerCorner;
  QPushButton*          _pushButtonSceneGraphNormalInvert;
  QLabel*               _labelSceneGraphEdges;
  QPushButton*          _pushButtonSceneGraphEdgesAdd;
  QPushButton*          _pushButtonSceneGraphEdgesRemove;
  QLabel*               _labelSceneIndexedFaceSets;
  QPushButton*          _pushButtonSceneGraphIndexedFaceSetsShow;
  QPushButton*          _pushButtonSceneGraphIndexedFaceSetsHide;
  QLabel*               _labelSceneIndexedLineSets;
  QPushButton*          _pushButtonSceneGraphIndexedLineSetsShow;
  QPushButton*          _pushButtonSceneGraphIndexedLineSetsHide;

  QLabel*               _labelPoints;
  QLineEdit*            _editPointsNumber;
  QCheckBox*            _checkBoxPointsHasNormals;
  QCheckBox*            _checkBoxPointsHasColors;
  QPushButton*          _pushButtonPointsRemove;
  QPushButton*          _pushButtonPointsShow;
  QPushButton*          _pushButtonPointsHide;

  QLabel*               _labelReconstruction;
  QLabel*               _labelSurfaceSinglePlane;
  QPushButton*          _pushButtonSurfaceSinglePlaneFit;
  QLineEdit*            _editSurfaceSinglePlaneCoefficient0;
  QLineEdit*            _editSurfaceSinglePlaneCoefficient1;
  QLineEdit*            _editSurfaceSinglePlaneCoefficient2;
  QLineEdit*            _editSurfaceSinglePlaneCoefficient3;
  QLabel*               _labelSurfaceMultiplePlane;
  QPushButton*          _pushButtonSurfaceMultiplePlanesFit;
  QLabel*               _labelSurfaceContinuous;
  QPushButton*          _pushButtonSurfaceContinuousFit;

  QLabel*               _labelSurface;
  QLabel*               _labelSurfaceVertices;
  QLineEdit*            _editSurfaceVertices;
  QLabel*               _labelSurfaceFaces;
  QLineEdit*            _editSurfaceFaces;
  QPushButton*          _pushButtonSurfaceRemove;
  QPushButton*          _pushButtonSurfaceShow;
  QPushButton*          _pushButtonSurfaceHide;

};

#endif // _WRL_TOOLSWIDGET_HPP_

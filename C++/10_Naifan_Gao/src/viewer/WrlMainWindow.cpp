//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-05 22:49:14 taubin>
//------------------------------------------------------------------------
//
// WrlMainWindow.cpp
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

#include "WrlMainWindow.hpp"
#include "WrlGLWidget.hpp"
#include "WrlAboutDialog.hpp"

#include <QApplication>
#include <QMenuBar>
#include <QGroupBox>
#include <QStatusBar>
#include <QFileDialog>

#include <io/LoaderWrl.hpp>
#include <io/SaverWrl.hpp>

int WrlMainWindow::_timerInterval = 20;

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::showStatusBarMessage(const QString & message) {
  _statusBar->showMessage(message);
}

//////////////////////////////////////////////////////////////////////
WrlMainWindow::WrlMainWindow() {
  setWindowIcon(QIcon("qt.icns"));

  LoaderWrl* wrlLoader = new LoaderWrl();
  _loader.registerLoader(wrlLoader);

  SaverWrl* wrlSaver = new SaverWrl();
  _saver.registerSaver(wrlSaver);

  QColor clearColor    = qRgb(75, 100, 150);
  QColor materialColor = qRgb(225, 150, 75);
  _glWidget    =  new WrlGLWidget(this, clearColor, materialColor);
  _toolsWidget = new WrlToolsWidget(this);

  QWidget * widget = new QWidget(this);
  setCentralWidget(widget);

  _centralLayout = new QGridLayout(widget);
  _centralLayout->setContentsMargins(5,5,5,5);
  _centralLayout->setSpacing(5);
  _centralLayout->addWidget(_glWidget,0,0,1,1);
  _centralLayout->addWidget(_toolsWidget,0,1,1,1);
  _centralLayout->setColumnMinimumWidth(0,600);
  _centralLayout->setColumnMinimumWidth(1,0);
  _centralLayout->setColumnStretch(0,10);
  _centralLayout->setColumnStretch(1,0);
  widget->setLayout(_centralLayout);
  _glWidget->show();
  _toolsWidget->hide();

  _statusBar = new QStatusBar(this);
  QFont font;
  font.setPointSize(9);
  _statusBar->setFont(font);
  setStatusBar(_statusBar);

  //////////////////////////////////////////////////
  QMenu *fileMenu = menuBar()->addMenu("&File");

  QAction *exit = new QAction("E&xit" , fileMenu);
  fileMenu->addAction(exit);
  connect(exit, SIGNAL(triggered(bool)),
          this, SLOT(onMenuFileExit()));
  
  QAction *load = new QAction("Load" , fileMenu);
  fileMenu->addAction(load);
  connect(load, SIGNAL(triggered(bool)),
          this, SLOT(onMenuFileLoad()));
  
  QAction *save = new QAction("Save" , fileMenu);
  fileMenu->addAction(save);
  connect(save, SIGNAL(triggered(bool)),
          this, SLOT(onMenuFileSave()));
  
  QAction *qtLogo = new QAction("Qt Logo" , fileMenu);
  fileMenu->addAction(qtLogo);
  connect(qtLogo, SIGNAL(triggered(bool)),
          _glWidget, SLOT(setQtLogo()));

  //////////////////////////////////////////////////
  QMenu *toolsMenu = menuBar()->addMenu("&Tools");

  QAction *showTools = new QAction("Show" , toolsMenu);
  toolsMenu->addAction(showTools);
  connect(showTools, SIGNAL(triggered(bool)),
          this, SLOT(onMenuToolsShow()));

  QAction *hideTools = new QAction("Hide" , toolsMenu);
  toolsMenu->addAction(hideTools);
  connect(hideTools, SIGNAL(triggered(bool)),
          this, SLOT(onMenuToolsHide()));

  //////////////////////////////////////////////////
  QMenu *helpMenu = menuBar()->addMenu("&Help");

  QAction *about = new QAction("About QtOpenGL",helpMenu);
  helpMenu->addAction(about);
  connect(about, SIGNAL(triggered(bool)),
           this, SLOT(onMenuHelpAbout()));

  // for animation
  _timer = new QTimer(this);
  _timer->setInterval(_timerInterval);
  connect(_timer, SIGNAL(timeout()), _glWidget, SLOT(update()));

  showStatusBarMessage("");
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuFileLoad() {

  std::string filename;

  // stop animation
  _timer->stop();

  QFileDialog fileDialog(this);
  fileDialog.setFileMode(QFileDialog::ExistingFile); // allowed to select only one 
  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setNameFilter(tr("VRML Files (*.wrl)"));
  QStringList fileNames;
  if(fileDialog.exec()) {
    fileNames = fileDialog.selectedFiles();
    if(fileNames.size()>0)
      filename = fileNames.at(0).toStdString();
  }

  if (filename.empty()) {
    showStatusBarMessage("load filename is empty");
  } else {

    static char str[1024];

    sprintf(str,"Loading \"%s\" ...",filename.c_str());
    showStatusBarMessage(QString(str));

    SceneGraph* pWrl = new SceneGraph();
    if(_loader.load(filename.c_str(),*pWrl)) { // if success
      sprintf(str,"Loaded \"%s\"",filename.c_str());
      pWrl->updateBBox();
      _glWidget->setSceneGraph(pWrl);
    } else {
      delete pWrl;
      sprintf(str,"Unable to load \"%s\"",filename.c_str());
    }

    showStatusBarMessage(QString(str));
  } 

  // restart animation
  _timer->start(_timerInterval);
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuFileSave() {

  std::string filename;

  // stop animation
  _timer->stop();

  QFileDialog fileDialog(this);
  fileDialog.setFileMode(QFileDialog::AnyFile); // allowed to select only one 
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  fileDialog.setNameFilter(tr("VRML Files (*.wrl)"));
  QStringList fileNames;
  if(fileDialog.exec()) {
    fileNames = fileDialog.selectedFiles();
    if(fileNames.size()>0)
      filename = fileNames.at(0).toStdString();
  }

  // restart animation
  _timer->start(_timerInterval);

  if (filename.empty()) {
    showStatusBarMessage("save filename is empty");
  } else {

    static char str[1024];

    sprintf(str,"Saving \"%s\" ...",filename.c_str());
    showStatusBarMessage(QString(str));

    SceneGraph* pWrl = _glWidget->getSceneGraph();

    if(_saver.save(filename.c_str(),*pWrl)) {
      sprintf(str,"Saved \"%s\"", filename.c_str());
    } else {
      sprintf(str,"Unable to save \"%s\"",filename.c_str());
    }

    showStatusBarMessage(QString(str));
  }
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuFileExit() {
  close();
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuToolsShow() {
  _centralLayout->setColumnMinimumWidth(1,300);
  _toolsWidget->show();
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuToolsHide() {
  _centralLayout->setColumnMinimumWidth(1,0);
  _toolsWidget->hide();
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::onMenuHelpAbout() {
  WrlAboutDialog dialog(this);
  dialog.exec();
}

//////////////////////////////////////////////////////////////////////
int WrlMainWindow::getGLWidgetWidth() {
  return _glWidget->size().width();
}

//////////////////////////////////////////////////////////////////////
int WrlMainWindow::getGLWidgetHeight() {
  return _glWidget->size().height();
}

//////////////////////////////////////////////////////////////////////
void WrlMainWindow::resizeEvent(QResizeEvent* /* event */) {
  _toolsWidget->updateState();
}

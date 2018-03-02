//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-05 22:20:51 taubin>
//------------------------------------------------------------------------
//
// SaverWrl.hpp
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

#ifndef _IFS_WRL_SAVER_HPP_
#define _IFS_WRL_SAVER_HPP_

#include "Saver.hpp"
#include <wrl/Shape.hpp>
#include <wrl/Appearance.hpp>
#include <wrl/Material.hpp>
#include <wrl/IndexedFaceSet.hpp>
#include <wrl/ImageTexture.hpp>
#include <wrl/Transform.hpp>
#include <wrl/SceneGraphTraversal.hpp>

class SaverWrl : public Saver {

private:

const static char* _ext;

public:

  SaverWrl()  {};
  ~SaverWrl() {};

  bool  save(const char* filename, SceneGraph& wrl);
  const char* ext() const { return _ext; }

private:

  // using C-style FILE pointers and fprintf() to save the files

  void saveAppearance
  (FILE* fp, string indent, Appearance* appearance);
  void saveGroup
  (FILE* fp, string indent, Group* group);
  void saveImageTexture
  (FILE* fp, string indent, ImageTexture* imageTexture);
  void saveIndexedFaceSet
  (FILE* fp, string indent, IndexedFaceSet* indexedFaceSet);
  void saveMaterial
  (FILE* fp, string indent, Material* material);
  void saveShape
  (FILE* fp, string indent, Shape* shape);
  void saveTransform
  (FILE* fp, string indent, Transform* transform);

};

#endif // _IFS_WRL_SAVER_HPP_

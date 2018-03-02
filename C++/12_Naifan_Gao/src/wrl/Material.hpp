//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:33:30 taubin>
//------------------------------------------------------------------------
//
// Material.hpp
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

#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

// Material {
//   exposedField SFFloat ambientIntensity 0.2
//   exposedField SFColor diffuseColor 0.8 0.8 0.8
//   exposedField SFColor emissiveColor 0 0 0
//   exposedField SFFloat shininess 0.2
//   exposedField SFColor specularColor 0 0 0
//   exposedField SFFloat transparency 0
// }

#include "Node.hpp"

using namespace std;

class Material : public Node {

private:

  float _ambientIntensity;
  Color _diffuseColor;
  Color _emissiveColor;
  float _shininess;
  Color _specularColor;
  float _transparency;

public:
  
  Material();
  virtual ~Material();

  float  getAmbientIntensity();
  Color& getDiffuseColor();
  Color& getEmissiveColor();
  float  getShininess();
  Color  getSpecularColor();
  float  getTransparency();

  void   setAmbientIntensity(float value);
  void   setDiffuseColor(Color& value);
  void   setEmissiveColor(Color&value);
  void   setShininess(float value);
  void   setSpecularColor(Color& value);
  void   setTransparency(float value);

  virtual bool    isMaterial() const { return true; }
  virtual string  getType()    const { return "Material"; }

  typedef bool    (*Property)(Material& material);
  typedef void    (*Operator)(Material& material);

  // can be used for debugging
  virtual void    printInfo(string indent);
};

#endif // _MATERIAL_HPP_

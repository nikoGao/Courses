//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2017-11-12 00:08:45 taubin>
//------------------------------------------------------------------------
//
// LoaderWrl.cpp
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


#include "Tokenizer.hpp"
#include "LoaderWrl.hpp"
#include "StrException.hpp"

#define VRML_HEADER "#VRML V2.0 utf8"

const char* LoaderWrl::_ext = "wrl";

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadSceneGraph(Tokenizer& tkn, SceneGraph& wrl) {

  bool   success = false;

  // TODO

  // only tokens to find at this level
    string name = "";
    while(tkn.get()) {
        if(tkn=="DEF"){
            tkn.get();
            name = tkn;
        }
        else if(tkn=="Group") {
            Group* g = new Group();
            g->setName(name);
            wrl.addChild(g);
            g->setParent(&wrl);
            loadGroup(tkn,*g);
        } else if(tkn=="Transform") {
            Transform* t = new Transform();
            t->setName(name);
            wrl.addChild(t);
            t->setParent(&wrl);
            loadTransform(tkn, *t);
        } else if(tkn=="Shape") {
            Shape* s = new Shape();
            s->setName(name);
            wrl.addChild(s);
            s->setParent(&wrl);
            loadShape(tkn, *s);
        } else if(tkn=="}") {
            break;
        } else {
            // fprintf(stderr,"tkn=\"%s\"\n",tkn.c_str());
            throw new StrException("unexpected token while parsing Group");
        }
    }
    success = true;
  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadGroup(Tokenizer& tkn, Group& group) {

  // Group {
  //   MFNode children    []
  //   SFVec3f bboxCenter  0 0 0
  //   SFVec3f bboxSize   -1 -1 -1
  // }

  // Group {
  //   MFNode children    []
  //   SFVec3f bboxCenter  0 0 0
  //   SFVec3f bboxSize   -1 -1 -1
  // }
    bool success = false;
    if(!tkn.expecting("{"))
    throw new StrException("expecting \"{\"");
    while(success==false && tkn.get()) {
        if(tkn=="children") {
            // TODO ...
            if(!tkn.expecting("[")){
                throw new StrException("expectiong \"[\"");
            }
            loadChildren(tkn, group);
        }else if(tkn=="bboxCenter"){
            tkn.get();
            double x = atof(tkn.c_str());
            tkn.get();
            double y = atof(tkn.c_str());
            tkn.get();
            double z = atof(tkn.c_str());
            Vec3f vec3(x, y, z);
            group.getBBoxCenter()=vec3;
        } else if(tkn=="bboxSize"){
            tkn.get();
            double x = atof(tkn.c_str());
            tkn.get();
            double y = atof(tkn.c_str());
            tkn.get();
            double z = atof(tkn.c_str());
            Vec3f vec3(x, y, z);
            group.getBBoxSize()=vec3;
        }else if(tkn=="}") {
            success = true;
        } else {
            throw new StrException("unexpected token while parsing Group");
        }
    }

  // TODO

  return success;
}

bool LoaderWrl::loadTransform(Tokenizer& tkn, Transform& transform) {

  // Transform {
  //   MFNode     children          []
  //   SFVec3f    bboxCenter        0 0 0
  //   SFVec3f    bboxSize          -1 -1 -1
  //   SFVec3f    center            0 0 0
  //   SFRotation rotation          0 0 1 0
  //   SFVec3f    scale             1 1 1
  //   SFRotation scaleOrientation  0 0 1 0
  //   SFVec3f    translation       0 0 0
  // }

  bool success = false;

  // TODO
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    while(success==false && tkn.get()) {
        if(tkn=="children") {
            
            // TODO ...
            if(!tkn.expecting("[")){
                throw new StrException("expectiong \"[\"");
            }
            loadChildren(tkn, transform);
        } else if(tkn=="center") {
            
            // TODO ...
            tkn.get();
            float x = atof(tkn.c_str());
            tkn.get();
            float y = atof(tkn.c_str());
            tkn.get();
            float z = atof(tkn.c_str());
            Vec3f vec3(x, y, z);
            transform.setCenter(vec3);
            
        } else if(tkn=="rotation") {
            
            // TODO ...
            tkn.get();
            float x = atof(tkn.c_str());
            tkn.get();
            float y = atof(tkn.c_str());
            tkn.get();
            float z = atof(tkn.c_str());
            tkn.get();
            float k = atof(tkn.c_str());
            Rotation rotation(x, y, z, k);
            transform.setRotation(rotation);
            
        } else if(tkn=="scale") {
            
            // TODO ...
            tkn.get();
            float x = atof(tkn.c_str());
            tkn.get();
            float y = atof(tkn.c_str());
            tkn.get();
            float z = atof(tkn.c_str());
            Vec3f vec3(x, y, z);
            transform.setScale(vec3);
            
        } else if(tkn=="scaleOrientation") {
            
            // TODO ...
            tkn.get();
            float x = atof(tkn.c_str());
            tkn.get();
            float y = atof(tkn.c_str());
            tkn.get();
            float z = atof(tkn.c_str());
            tkn.get();
            float k = atof(tkn.c_str());
            Rotation scaleOrientation(x, y, z, k);
            transform.setScaleOrientation(scaleOrientation);
            
        } else if(tkn=="translation") {
            
            // TODO ...
            tkn.get();
            float x = atof(tkn.c_str());
            tkn.get();
            float y = atof(tkn.c_str());
            tkn.get();
            float z = atof(tkn.c_str());
            Vec3f translation(x, y, z);
            transform.setTranslation(translation);
            
        } else if(tkn=="}") {
            success = true;
        } else {
            throw new StrException("unexpected token while parsing Group");
        }
    }
  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadChildren(Tokenizer& tkn, Group& group) {

  bool   success = false;

  // TODO
    while(tkn.get() && tkn !="]"){
        if(tkn=="Group") {
            Group* g = new Group();
            group.addChild(g);
            g->setParent(&group);
            loadGroup(tkn,*g);
            
        } else if(tkn=="Transform") {
            Transform* t = new Transform();
            group.addChild(t);
            t->setParent(&group);
            loadTransform(tkn, *t);
            
        } else if(tkn=="Shape") {
            Shape* s = new Shape();
            group.addChild(s);
            s->setParent(&group);
            loadShape(tkn, *s);
        } else if(tkn=="") {
            break;
        } else {
            // fprintf(stderr,"tkn=\"%s\"\n",tkn.c_str());
            throw new StrException("unexpected token while parsing Transform");
        }
    }
    success = true;

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadShape(Tokenizer& tkn, Shape& shape) {

  bool success = false;
    
  // DEF NAME Shape {
  //   SFNode appearance NULL
  //   SFNode geometry   NULL
  // }

  // or

  // Shape {
  //   SFNode appearance NULL
  //   SFNode geometry   NULL
  // }

  // TODO
    string name= "";
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    // TODO ...
    while(success==false && tkn.get()) {
        if(tkn=="appearance"){
            Appearance* appearance = new Appearance();
            shape.setAppearance(appearance);
            appearance->setParent(&shape);
            loadAppearance(tkn, *appearance);
        }else if(tkn=="geometry"){
            tkn.get();
            if(tkn=="DEF"){
                name = tkn;
                tkn.get();
            }
            if(tkn=="IndexedFaceSet"){
                IndexedFaceSet* indexedFaceSet = new IndexedFaceSet();
                indexedFaceSet->setName(name);
                shape.setGeometry(indexedFaceSet);
                indexedFaceSet->setParent(&shape);
                loadIndexedFaceSet(tkn, *indexedFaceSet);
            }else if(tkn=="IndexedLineSet"){
                IndexedLineSet* indexedLineSet = new IndexedLineSet();
                indexedLineSet->setName(name);
                indexedLineSet->setParent(&shape);
                shape.setGeometry(indexedLineSet);
                loadIndexedLineSet(tkn, *indexedLineSet);
            }
        }else if(tkn=="}"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing Transform");
        }
    }

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadAppearance(Tokenizer& tkn, Appearance& appearance) {

  // DEF NAME Appearance {
  //   SFNode material NULL
  //   SFNode texture NULL
  //   // SFNode textureTransform NULL
  // }

  // or

  // Appearance {
  //   SFNode material NULL
  //   SFNode texture NULL
  //   // SFNode textureTransform NULL
  // }

  bool   success = false;

  // TODO
    tkn.get();
    appearance.setName(tkn);
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    // TODO ...
    while(success==false && tkn.get()) {
        if(tkn=="material"){
            Material* material = new Material();
            appearance.setMaterial(material);
            loadMaterial(tkn, *material);
        }else if(tkn=="texture"){
            ImageTexture* imageTexture = new ImageTexture();
            appearance.setTexture(imageTexture);
            loadImageTexture(tkn, *imageTexture);
        }else if(tkn=="}"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing Appearance");
        }
    }
    return success;
  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadMaterial(Tokenizer& tkn, Material& material) {

  // DEF NAME Material {
  //   SFFloat ambientIntensity 0.2
  //   SFColor diffuseColor     0.8 0.8 0.8
  //   SFColor emissiveColor    0 0 0
  //   SFFloat shininess        0.2
  //   SFColor specularColor    0 0 0
  //   SFFloat transparency     0
  // }

  // or

  // Material {
  //   SFFloat ambientIntensity 0.2
  //   SFColor diffuseColor     0.8 0.8 0.8
  //   SFColor emissiveColor    0 0 0
  //   SFFloat shininess        0.2
  //   SFColor specularColor    0 0 0
  //   SFFloat transparency     0
  // }

  bool success = false;

  // TODO
    tkn.get();
    material.setName(tkn);
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    // TODO ...
    while(success==false && tkn.get()) {
        if(tkn=="ambientIntensity"){
            tkn.get();
            float ambientIntensity=atof(tkn.c_str());
            material.setAmbientIntensity(ambientIntensity);
        }else if(tkn=="diffuseColor"){
            tkn.get();
            double x = atof(tkn.c_str());
            tkn.get();
            double y = atof(tkn.c_str());
            tkn.get();
            double z = atof(tkn.c_str());
            Color color(x, y, z);
            material.setDiffuseColor(color);
        }else if(tkn=="emissiveColor"){
            tkn.get();
            double x = atof(tkn.c_str());
            tkn.get();
            double y = atof(tkn.c_str());
            tkn.get();
            double z = atof(tkn.c_str());
            Color color(x, y, z);
            material.setEmissiveColor(color);
        }else if(tkn=="shininess"){
            tkn.get();
            float shininess=atof(tkn.c_str());
            material.setShininess(shininess);
        }else if(tkn=="specularColor"){
            tkn.get();
            double x = atof(tkn.c_str());
            tkn.get();
            double y = atof(tkn.c_str());
            tkn.get();
            double z = atof(tkn.c_str());
            Color color(x, y, z);
            material.setSpecularColor(color);
        }else if(tkn=="transparency"){
            tkn.get();
            float transparency=atof(tkn.c_str());
            material.setTransparency(transparency);
        }else if(tkn=="}"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing Material");
        }
    }
  return success;

}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadImageTexture(Tokenizer& tkn, ImageTexture& imageTexture) {

  // DEF NAME ImageTexture {
  //   MFString url []
  //   SFBool repeatS TRUE
  //   SFBool repeatT TRUE
  // }

  // or

  // ImageTexture {
  //   MFString url []
  //   SFBool repeatS TRUE
  //   SFBool repeatT TRUE
  // }

  bool success = false;

  // TODO
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    // TODO ...
    while(success==false && tkn.get()) {
        if(tkn=="url"){
            if(tkn.expecting("[")) throw new StrException("expecting \"[\"");
            while(tkn.get() && tkn!="]"){
                if(tkn.substr(tkn.length()-3)=="JPG"||tkn.substr(tkn.length()-4)=="JPEG"||tkn.substr(tkn.length()-3)=="PNG"||tkn.substr(tkn.length()-3)=="GIF")
                imageTexture.adToUrl(tkn);
                else throw new StrException("invalid imageTexture");
            }
        }else if(tkn=="repeatS"){
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            imageTexture.setRepeatS(b);
        }else if(tkn=="repearT"){
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            imageTexture.setRepeatT(b);
        }else if(tkn=="}"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing ImageTexture");
        }
    }
  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadIndexedFaceSet(Tokenizer& tkn, IndexedFaceSet& ifs) {

  // DEF NAME IndexedFaceSet {
  //   SFNode  color             NULL
  //   SFNode  coord             NULL
  //   SFNode  normal            NULL
  //   SFNode  texCoord          NULL
  //   SFBool  ccw               TRUE
  //   MFInt32 colorIndex        []        # [-1,)
  //   SFBool  colorPerVertex    TRUE
  //   SFBool  convex            TRUE
  //   MFInt32 coordIndex        []        # [-1,)
  //   SFFloat creaseAngle       0         # [ 0,)
  //   MFInt32 normalIndex       []        # [-1,)
  //   SFBool  normalPerVertex   TRUE
  //   SFBool  solid             TRUE
  //   MFInt32 texCoordIndex     []        # [-1,)
  // }

  // or

  // IndexedFaceSet {
  //   SFNode  color             NULL
  //   SFNode  coord             NULL
  //   SFNode  normal            NULL
  //   SFNode  texCoord          NULL
  //   SFBool  ccw               TRUE
  //   MFInt32 colorIndex        []        # [-1,)
  //   SFBool  colorPerVertex    TRUE
  //   SFBool  convex            TRUE
  //   MFInt32 coordIndex        []        # [-1,)
  //   SFFloat creaseAngle       0         # [ 0,)
  //   MFInt32 normalIndex       []        # [-1,)
  //   SFBool  normalPerVertex   TRUE
  //   SFBool  solid             TRUE
  //   MFInt32 texCoordIndex     []        # [-1,)
  // }

  bool success = false;

  // TODO
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    while(success==false && tkn.get()){
        if(tkn=="solid"||tkn=="solid\r"||tkn=="solid\n"||tkn=="solid\r\n") {
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
            }
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for solid");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.getSolid()=b;
        }
        else if(tkn=="coord"||tkn=="coord\r"||tkn=="coord\n"||tkn=="coord\r\n"){
            if(!tkn.expecting("Coordinate"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("point"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            int count = 0;
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0 || count%3==2){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                    count++;
                }else{
                    count++;
                }
                float coord = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw 4;
                    return success;
                }else{
                    ifs.getCoord().push_back(coord);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="coordIndex"||tkn=="coordIndex\r"||tkn=="coordIndex\r\n"||tkn=="coordIndex\n"){
            if(!tkn.expecting("[")){
                throw new StrException("Error loading file: missing '[' in the file");
            }
            while(tkn.get() && tkn!="]"){
                int index = atoi(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()||(index < -1)){
                    throw new StrException("Error loading file: Invalid coordIndex point");
                    //                          return success;
                }else{
                    ifs.getCoordIndex().push_back(index);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
        }else if(tkn=="color"||tkn=="color\r"||tkn=="color\n"||tkn=="color\r\n"){
            if(!tkn.expecting("Color"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("color"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            unsigned count=0;
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0||count%3==2){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                    count++;
                }else{
                    count++;
                }
                float color = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw new StrException("Error loading file: error color value");
                    return success;
                }else{
                    ifs.getColor().push_back(color);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="colorIndex"||tkn=="colorIndex\r"||tkn=="colorIndex\r\n"||tkn=="colorIndex\n"){
            if(!tkn.expecting("[")){
                throw new StrException("Error loading file: missing '[' in the file");
            }
            while(tkn.get() && tkn!="]"){
                int index = atoi(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()||index<-1){
                    throw new StrException("Error loading file: Invalid colorIndex point");
                    return success;
                }else{
                    ifs.getColorIndex().push_back(index);
                }
            }
        }
        else if(tkn=="colorPerVertex"||tkn=="colorPerVertex\r"||tkn=="colorPerVertex\n"||tkn=="colorPerVertex\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for colorPerVertex");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.setColorPerVertex(b);
        }else if(tkn=="texCoord"||tkn=="texCoord\r"||tkn=="texCoord\n"||tkn=="texCoord\r\n"){
            if(!tkn.expecting("TextureCoordinate"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new  StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("point"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                }
                float texcoord = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw new StrException("Error loading file: error textureCoordinate value");
                }else{
                    ifs.getTexCoord().push_back(texcoord);
                }
            }
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="texCoordIndex"||tkn=="texCoordIndex\r"||tkn=="texCoordIndex\n"||tkn=="texCoordIndex\r\n"){
            if(!tkn.expecting("[")){
                throw new StrException("Error loading file: missing '[' in the file");
            }
            while(tkn.get() && tkn!="]"){
                int index = atoi(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()||index<-1){
                    throw new StrException("Error loading file: Invalid texCoordIndex point");
                }else{
                    ifs.getTexCoordIndex().push_back(index);
                }
            }
        }
        else if(tkn=="normalPerVertex"||tkn=="normalPerVertex\r"||tkn=="normalPerVertex\n"||tkn=="normalPerVertex\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for normalPerVertex");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.setNormalPerVertex(b);
        }else if(tkn=="normal"||tkn=="normal\r"||tkn=="normal\n"||tkn=="normal\r\n"){
            if(!tkn.expecting("Normal"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("vector"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                }
                float normal = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw new StrException("Error loading file: error normal value");
                    return success;
                }else{
                    ifs.getNormal().push_back(normal);
                }
            }
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="ccw"||tkn=="ccw\r"||tkn=="ccw\n"||tkn=="ccw\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for ccw");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.getCcw()=b;
        }else if(tkn=="convex"||tkn=="convex\r"||tkn=="convex\n"||tkn=="convex\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for convex");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.getConvex()=b;
        }else if(tkn=="creaseAngle"||tkn=="creaseAngle\r"||tkn=="creaseAngle\n"||tkn=="creaseAngle\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for creaseAngle");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.getCreaseangle()=b;
        }
        else if(tkn=="}"||tkn=="}\r"||tkn=="}\n"||tkn=="}\r\n"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing IndexedFaceSet");
        }
    }

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadIndexedLineSet(Tokenizer& tkn, IndexedLineSet& ifs) {

  // DEF NAME IndexedLineSet {
  //   SFNode  coord             NULL
  //   MFInt32 coordIndex        []        # [-1,)
  //   SFNode  color             NULL
  //   MFInt32 colorIndex        []        # [-1,)
  //   SFBool  colorPerVertex    TRUE
  // }

  // or

  // IndexedLineSet {
  //   SFNode  coord             NULL
  //   MFInt32 coordIndex        []        # [-1,)
  //   SFNode  color             NULL
  //   MFInt32 colorIndex        []        # [-1,)
  //   SFBool  colorPerVertex    TRUE
  // }

  bool success = false;

  // TODO
    if(tkn.expecting("{")==false)
    throw new StrException("expecting \"{\"");
    while(success==false && tkn.get()){
        if(tkn=="coord"||tkn=="coord\r"||tkn=="coord\n"||tkn=="coord\r\n"){
            if(!tkn.expecting("Coordinate"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("point"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            int count = 0;
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0 || count%3==2){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                    count++;
                }else{
                    count++;
                }
                float coord = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw 4;
                    return success;
                }else{
                    ifs.getCoord().push_back(coord);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="coordIndex"||tkn=="coordIndex\r"||tkn=="coordIndex\r\n"||tkn=="coordIndex\n"){
            if(!tkn.expecting("[")){
                throw new StrException("Error loading file: missing '[' in the file");
            }
            while(tkn.get() && tkn!="]"){
                int index = atoi(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()||(index < -1)){
                    throw new StrException("Error loading file: Invalid coordIndex point");
                    //                          return success;
                }else{
                    ifs.getCoordIndex().push_back(index);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
        }else if(tkn=="color"||tkn=="color\r"||tkn=="color\n"||tkn=="color\r\n"){
            if(!tkn.expecting("Color"))
            throw new StrException("Error loading file: missing coord name");
            if(!tkn.expecting("{"))
            throw new StrException("Error loading file: missing '{' in the file");
            if(!tkn.expecting("color"))
            throw new StrException("Error loading file: missing 'point'");
            if(!tkn.expecting("["))
            throw new StrException("Error loading file: missing '[' in the file");
            unsigned count=0;
            while(tkn.get() && tkn!="]"){
                if(tkn.compare(tkn.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0||count%3==2){
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\r'), tkn.end());
                    tkn.erase(std::remove(tkn.begin(), tkn.end(), '\n'), tkn.end());
                    count++;
                }else{
                    count++;
                }
                float color = atof(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()){
                    throw new StrException("Error loading file: error color value");
                    return success;
                }else{
                    ifs.getColor().push_back(color);
                }
            }
            if(tkn!="]") throw new StrException("Missing ']' in the file");
            if(!tkn.expecting("}")){
                throw new StrException("Error loading file: missing '}' in the file");
            }
        }else if(tkn=="colorIndex"||tkn=="colorIndex\r"||tkn=="colorIndex\r\n"||tkn=="colorIndex\n"){
            if(!tkn.expecting("[")){
                throw new StrException("Error loading file: missing '[' in the file");
            }
            while(tkn.get() && tkn!="]"){
                int index = atoi(tkn.c_str());
                char* endPtr;
                strtod(tkn.c_str(), &endPtr);
                int length = endPtr-tkn.c_str();
                if(length != tkn.length()||index<-1){
                    throw new StrException("Error loading file: Invalid colorIndex point");
                    return success;
                }else{
                    ifs.getColorIndex().push_back(index);
                }
            }
        }else if(tkn=="colorPerVertex"||tkn=="colorPerVertex\r"||tkn=="colorPerVertex\n"||tkn=="colorPerVertex\r\n"){
            if(!tkn.get()) throw new StrException("Error loading file: hit the end of the file");
            string value = tkn;
            std::transform(value.begin(), value.end(), value.begin(), ::tolower);
            if(!value.compare("true") && !value.compare("false")){
                throw new StrException("Error loading file: no set value for colorPerVertex");
            }
            std::istringstream is(value);
            bool b;
            is >> std::boolalpha >> b;
            ifs.setColorPerVertex(b);
        }else if(tkn=="}"||tkn=="}\r"||tkn=="}\n"||tkn=="}\r\n"){
            success=true;
        }else{
            throw new StrException("unexpected token while parsing IndexedFaceSet");
        }
    }

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadVecFloat(Tokenizer&tkn,vector<float>& vec) {

  bool success = false;

  // TODO

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadVecInt(Tokenizer&tkn,vector<int>& vec) {

  bool success = false;

  // TODO

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::loadVecString(Tokenizer&tkn,vector<string>& vec) {

  bool success = false;

  // TODO

  return success;
}

//////////////////////////////////////////////////////////////////////
bool LoaderWrl::load(const char* filename, SceneGraph& wrl) {

  bool success = false;

  try {

    // open the file
      ifstream ifs(filename);
    // clear the container
    wrl.clear();
    // save the filename
    wrl.setUrl(filename);

    // read and check header line
    char header[32] = "";
    // first line of file must be equal to VRML_HEADER
      ifs.getline(header,32);
      string str=header;
      str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    if(string(str)!=VRML_HEADER) throw new StrException("header!=VRM_HEADER");

    // create a Tokenizer and start parsing
    Tokenizer tkn(ifs);
    bool res = loadSceneGraph(tkn,wrl);
      wrl.updateBBox(true);
      ifs.close();
    // if we have reached this point we have succeeded
    // close file
      if(res && !tkn.get())
    success = true;

  } catch(StrException* e) { 

    // if we catch an exception
    // 1) close file if still open
    // 2) print an error message
    // 3) delete e;
    // 4) clear the wrl container
    // 5) clear the wrl container url field
      cerr << "ERROR | " << e->what() << endl;
      delete e;
      wrl.clear();
      wrl.setUrl("");
    success = false; 

  }

  return success;
}

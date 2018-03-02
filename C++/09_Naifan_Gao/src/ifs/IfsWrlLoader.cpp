// AUTHOR : Naifan Gao <naifan_gao@brown.edu>
//
// IfsLoader.cpp
//

#include "IfsWrlLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#define VRML_HEADER "#VRML V2.0 utf8"

const char* IfsWrlLoader::_ext = "wrl";

bool IfsWrlLoader::load(const char* filename, Ifs& ifs) {
  bool success = false;
    unsigned line_num = 1;
    unsigned face = 0;
    unsigned color = 0;
    unsigned texcoord = 0;
  if(filename!=(char*)0) {
    // TODO
      ifstream ifstr(filename);
      char cstr[512];
      ifstr.getline(cstr,512);
      string str=cstr;
      str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
      if(str!=VRML_HEADER){
          cerr << "Line: "<< line_num << ": Error: iftest: Invalid WRL file." << endl;
          return success;
      }
      line_num++;
      Tokenizer tokenizer(ifstr);
      while(tokenizer!="IndexedFaceSet"){
          try{
              if(tokenizer.get()){
                  if(tokenizer=="{"||tokenizer=="["||tokenizer=="]"||tokenizer=="}"||
                     tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                      line_num++;
                  }
              }else throw 0;
          }catch(int e){
              cerr << "Line " << line_num << ": Error wrl file: Not found IndexedFaceSet;" << endl;
          }
      }
      try{
          if(!tokenizer.expecting("{")){
              throw 0;
          }
          line_num++;
      }catch(int e){
          cerr <<"Line "<< line_num <<": Error ifsTest: WRL file structure error;" << endl;
      }
      while(tokenizer.get()){
          if(tokenizer=="solid"||tokenizer=="solid\r"||tokenizer=="solid\n"||tokenizer=="solid\r\n") {
              try{
                  if(!tokenizer.get()) throw 1;
                  if(tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                      line_num++;
                  }
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                  if(!value.compare("true") && !value.compare("false")){
                      throw 0;
                  }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setSolid(b);
              }catch(int e){
                  switch(e){
                      case 0: cerr <<"Line " << line_num << ": Error loading file: no set value for solid;" << endl; break;
                      case 1: cerr <<"Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }
          else if(tokenizer=="coord"||tokenizer=="coord\r"||tokenizer=="coord\n"||tokenizer=="coord\r\n"){
              try{
              if(!tokenizer.expecting("Coordinate"))
                  throw 0;
              if(!tokenizer.expecting("{"))
                  throw 1;
              else line_num++;
              if(!tokenizer.expecting("point"))
                  throw 2;
              if(!tokenizer.expecting("["))
                  throw 3;
              else line_num++;
                  int count = 0;
              while(tokenizer.get() && tokenizer!="]"){
                  if(tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0 || count%3==2){
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                      line_num++;
                      count++;
                  }else{
                      count++;
                  }
                  float coord = atof(tokenizer.c_str());
                  char* endPtr;
                  strtod(tokenizer.c_str(), &endPtr);
                  int length = endPtr-tokenizer.c_str();
                  if(length != tokenizer.length()){
                      throw 4;
                      return success;
                  }else{
                      ifs.setCoord(coord);
                  }
              }
                  if(tokenizer=="]")
                      line_num++;
              if(!tokenizer.expecting("}")){
                  throw 5;
              }else line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: missing coord name;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: missing '{' in the file;" << endl; break;
                      case 2: cerr << "Line " << line_num << ": Error loading file: missing 'point';" << endl; break;
                      case 3: cerr << "Line " << line_num << ": Error loading file: missing '[' in the file;" << endl; break;
                      case 4: cerr << "Line " << line_num << ": Error loading file: error cooridnate value;" << endl; break;
                      case 5: cerr << "Line " << line_num << ": Error loading file: missing '}' in the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="coordIndex"||tokenizer=="coordIndex\r"||tokenizer=="coordIndex\r\n"||tokenizer=="coordIndex\n"){
              try{
                  if(!tokenizer.expecting("[")){
                      throw 0;
                  }else line_num++;
                  while(tokenizer.get() && tokenizer!="]"){
                      int index = atoi(tokenizer.c_str());
                      char* endPtr;
                      strtod(tokenizer.c_str(), &endPtr);
                      int length = endPtr-tokenizer.c_str();
                      if(length != tokenizer.length()||(index < -1)){
                          throw 1;
//                          return success;
                      }else{
                          ifs.setCoordIndex(index);
                          if(index==-1) {
                              face++;
                              line_num++;
                          }
                      }
                  }
                  if(tokenizer=="]") line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr <<"Line " << line_num << ": Error loading file: missing '[' in the file;" << endl; break;
                      case 1: cerr <<"Line " << line_num << ": Error loading file: Invalid coordIndex point" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="color"||tokenizer=="color\r"||tokenizer=="color\n"||tokenizer=="color\r\n"){
              try{
                  if(!tokenizer.expecting("Color"))
                      throw 0;
                  if(!tokenizer.expecting("{"))
                      throw 1;
                  else line_num++;
                  if(!tokenizer.expecting("color"))
                      throw 2;
                  if(!tokenizer.expecting("["))
                      throw 3;
                  else line_num++;
                  unsigned count=0;
                  while(tokenizer.get() && tokenizer!="]"){
                      if(tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0||count%3==2){
                          tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                          tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                          line_num++;
                          count++;
                      }else{
                          count++;
                      }
                      float color = atof(tokenizer.c_str());
                      char* endPtr;
                      strtod(tokenizer.c_str(), &endPtr);
                      int length = endPtr-tokenizer.c_str();
                      if(length != tokenizer.length()){
                          throw 4;
                          return success;
                      }else{
                          ifs.setColor(color);
                      }
                  }
                  if(tokenizer=="]") line_num++;
                  if(!tokenizer.expecting("}")){
                      throw 5;
                  }else line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr <<"Line " << line_num << ": Error loading file: missing coord name;" << endl; break;
                      case 1: cerr <<"Line " << line_num << ": Error loading file: missing '{' in the file;" << endl; break;
                      case 2: cerr <<"Line " << line_num << ": Error loading file: missing 'point';" << endl; break;
                      case 3: cerr <<"Line " << line_num << ": Error loading file: missing '[' in the file;" << endl; break;
                      case 4: cerr <<"Line " << line_num << ": Error loading file: error color value;" << endl; break;
                      case 5: cerr <<"Line " << line_num << ": Error loading file: missing '}' in the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="colorIndex"||tokenizer=="colorIndex\r"||tokenizer=="colorIndex\r\n"||tokenizer=="colorIndex\n"){
              try{
                  if(!tokenizer.expecting("[")){
                      throw 0;
                  }
                  while(tokenizer.get() && tokenizer!="]"){
                      int index = atoi(tokenizer.c_str());
                      char* endPtr;
                      strtod(tokenizer.c_str(), &endPtr);
                      int length = endPtr-tokenizer.c_str();
                      if(length != tokenizer.length()||index<-1){
                          throw 1;
                          return success;
                      }else{
                          if(index==-1) {
                              color++;
                              line_num++;
                          }
                          ifs.setColorIndex(index);
                      }
                  }
                  if(tokenizer=="]") line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr <<"Line " << line_num << ": Error loading file: missing '[' in the file;"; break;
                      case 1: cerr <<"Line " << line_num << ": Error loading file: Invalid colorIndex point"; break;
                  }
                  return success;
              }
          }
          else if(tokenizer=="colorPerVertex"||tokenizer=="colorPerVertex\r"||tokenizer=="colorPerVertex\n"||tokenizer=="colorPerVertex\r\n"){
              try{
                  if(!tokenizer.get()) throw 1;
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                      if(!value.compare("true") && !value.compare("false")){
                          throw 0;
                      }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setColorPerVertex(b);
                  line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: no set value for colorPerVertex;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="texCoord"||tokenizer=="texCoord\r"||tokenizer=="texCoord\n"||tokenizer=="texCoord\r\n"){
              try{
              if(!tokenizer.expecting("TextureCoordinate"))
                  throw 0;
              if(!tokenizer.expecting("{"))
                  throw 1;
              else line_num++;
              if(!tokenizer.expecting("point"))
                  throw 2;
              if(!tokenizer.expecting("["))
                  throw 3;
              else line_num++;
              while(tokenizer.get() && tokenizer!="]"){
                  if(tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                      line_num++;
                  }
                  float texcoord = atof(tokenizer.c_str());
                  char* endPtr;
                  strtod(tokenizer.c_str(), &endPtr);
                  int length = endPtr-tokenizer.c_str();
                  if(length != tokenizer.length()){
                      throw 4;
                      return success;
                  }else{
                      ifs.setTexCoord(texcoord);
                  }
              }
              if(tokenizer=="]") line_num++;
              if(!tokenizer.expecting("}")){
                  throw 5;
              }else line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << "Error loading file: missing coord name;" << endl; break;
                      case 1: cerr << "Line " << line_num << "Error loading file: missing '{' in the file;" << endl; break;
                      case 2: cerr << "Line " << line_num << "Error loading file: missing 'point';" << endl; break;
                      case 3: cerr << "Line " << line_num << "Error loading file: missing '[' in the file;" << endl; break;
                      case 4: cerr << "Line " << line_num << "Error loading file: error textureCoordinate value;" << endl; break;
                      case 5: cerr << "Line " << line_num << "Error loading file: missing '}' in the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="texCoordIndex"||tokenizer=="texCoordIndex\r"||tokenizer=="texCoordIndex\n"||tokenizer=="texCoordIndex\r\n"){
              try{
                  if(!tokenizer.expecting("[")){
                      throw 0;
                  }
                  while(tokenizer.get() && tokenizer!="]"){
                      int index = atoi(tokenizer.c_str());
                      char* endPtr;
                      strtod(tokenizer.c_str(), &endPtr);
                      int length = endPtr-tokenizer.c_str();
                      if(length != tokenizer.length()||index<-1){
                          throw 0;
                          return success;
                      }else{
                          if(index==-1) {
                              texcoord++;
                              line_num++;
                          }
                          ifs.setTexCoordIndex(index);
                      }
                  }
                  if(tokenizer=="]") line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: missing '[' in the file;"; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: Invalid texCoordIndex point"; break;
                  }
                  return success;
              }
          }
          else if(tokenizer=="normalPerVertex"||tokenizer=="normalPerVertex\r"||tokenizer=="normalPerVertex\n"||tokenizer=="normalPerVertex\r\n"){
              try{
                  if(!tokenizer.get()) throw 1;
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                  if(!value.compare("true") && !value.compare("false")){
                      throw 0;
                  }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setNormalPerVertex(b);
                  line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: no set value for normalPerVertex;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="normal"||tokenizer=="normal\r"||tokenizer=="normal\n"||tokenizer=="normal\r\n"){
              try{
              if(!tokenizer.expecting("Normal"))
                  throw 0;
              if(!tokenizer.expecting("{"))
                  throw 1;
              else line_num++;
              if(!tokenizer.expecting("vector"))
                  throw 2;
              if(!tokenizer.expecting("["))
                  throw 3;
              else line_num++;
              while(tokenizer.get() && tokenizer!="]"){
                  if(tokenizer.compare(tokenizer.size() - string(1,'\n').size(), string(1,'\n').size(), string(1,'\n')) == 0){
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\r'), tokenizer.end());
                      tokenizer.erase(std::remove(tokenizer.begin(), tokenizer.end(), '\n'), tokenizer.end());
                      line_num++;
                  }
                  float normal = atof(tokenizer.c_str());
                  char* endPtr;
                  strtod(tokenizer.c_str(), &endPtr);
                  int length = endPtr-tokenizer.c_str();
                  if(length != tokenizer.length()){
                      throw 4;
                      return success;
                  }else{
                      ifs.setNormal(normal);
                  }
              }
                  if(tokenizer=="]") line_num++;
              if(!tokenizer.expecting("}")){
                  throw 5;
              }else line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: missing coord name;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: missing '{' in the file;" << endl; break;
                      case 2: cerr << "Line " << line_num << ": Error loading file: missing 'point';" << endl; break;
                      case 3: cerr << "Line " << line_num << ": Error loading file: missing '[' in the file;" << endl; break;
                      case 4: cerr << "Line " << line_num << ": Error loading file: error normal value;" << endl; break;
                      case 5: cerr << "Line " << line_num << ": Error loading file: missing '}' in the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="ccw"||tokenizer=="ccw\r"||tokenizer=="ccw\n"||tokenizer=="ccw\r\n"){
              try{
                  if(!tokenizer.get()) throw 1;
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                  if(!value.compare("true") && !value.compare("false")){
                      throw 0;
                  }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setCcw(b);
                  line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: no set value for ccw;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="convex"||tokenizer=="convex\r"||tokenizer=="convex\n"||tokenizer=="convex\r\n"){
              try{
                  if(!tokenizer.get()) throw 1;
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                  if(!value.compare("true") && !value.compare("false")){
                      throw 0;
                  }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setConvex(b);
                  line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: no set value for convex;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }else if(tokenizer=="creaseAngle"||tokenizer=="creaseAngle\r"||tokenizer=="creaseAngle\n"||tokenizer=="creaseAngle\r\n"){
              try{
                  if(!tokenizer.get()) throw 1;
                  string value = tokenizer;
                  std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                  if(!value.compare("true") && !value.compare("false")){
                      throw 0;
                  }
                  std::istringstream is(value);
                  bool b;
                  is >> std::boolalpha >> b;
                  ifs.setCreaseangle(b);
                  line_num++;
              }catch(int e){
                  switch(e){
                      case 0: cerr << "Line " << line_num << ": Error loading file: no set value for creaseAngle;" << endl; break;
                      case 1: cerr << "Line " << line_num << ": Error loading file: hit the end of the file;" << endl; break;
                  }
                  return success;
              }
          }
          else if(tokenizer=="}"||tokenizer=="}\r"||tokenizer=="}\n"||tokenizer=="}\r\n"){
              break;
          }else{
              cerr << "Line " << line_num << ": Error: unfound unexpected end token while parsing IndexedFaceSet;"<< endl;
              return success;
          }
      }
      ifstr.close();
      success = true;
  }
    if(success){
        ifs.setNumberOfFaces(face);
        ifs.setNumberOfCorners(ifs.getCoord().size()/3);
        ifs.setNumberOfCoord(ifs.getCoord().size()/4);
        ifs.setNumberOfTexCoord(ifs.getTexCoord().size()/3);
        ifs.setNumberOfNormal(ifs.getNormal().size()/3);
        if(ifs.getColor().empty()){
            ifs.setNumberOfColor(1);
        }
        else if(ifs.getColorPerVertex()){
            if(ifs.getColorIndex().empty())
                ifs.setNumberOfColor(ifs.getColor().size()/3);
            else ifs.setNumberOfColor(ifs.getColorIndex().size());
        }else{
            if(!ifs.getColorIndex().empty()){
                ifs.setNumberOfColor(color);
            }else{
                ifs.setNumberOfColor(ifs.getColor().size()/3);
            }
        }
//        if(ifs.getCoord().empty()||ifs.getCoordIndex().empty()){
//            success = false;
//            cerr << "Error Loading file: no geometry found;" << endl;
//        }
//        Ifs::Binding normal = ifs.getNormalBinding();
//        Ifs::Binding color = ifs.getColorBinding();
//        Ifs::Binding coord = ifs.getTexCoordBinding();
//        if(normal==Ifs::Binding::PB_NONE && color==Ifs::Binding::PB_NONE && coord==Ifs::Binding::PB_NONE){
//            success=false;
//            cerr << "Error Loading file: no geometry found;" << endl;
//        }
//
    }
    
  return success;
}


// AUTHOR : Your Name <your_email@brown.edu>
//
// IfsWrlSaver.cpp
//

#include "IfsWrlSaver.hpp"
#include <fstream>
#include <iostream>
using namespace std;

const char* IfsWrlSaver::_ext = "wrl";

bool IfsWrlSaver::save(const char* filename, Ifs& ifs) {
  bool success = false;
  if(filename!=(char*)0) {
    // TODO
      ofstream ofstr(filename);
      ofstr << "#VRML V2.0 utf8" << endl;
      ofstr << " Shape {" << endl;
      ofstr << "\tgeometry IndexedFaceSet {" << endl;
      ofstr << "\t solid ";
      if(ifs.getSolid())
          ofstr << "TRUE" << endl;
      else ofstr << "FALSE" << endl;
      if(!ifs.getCoord().empty()){
          ofstr << "\t\tcoord Coordinate {" << endl;
          ofstr << "\t\t point [" << endl;
          int i = 0;
          for(std::vector<float>::iterator it=ifs.getCoord().begin(); it != ifs.getCoord().end(); it++){
              ofstr.precision(6);
              ofstr.setf(ios::fixed);
              ofstr.setf(ios::showpoint);
              if(i%3==0) ofstr << "\t\t";
              if(i%3==2){
                  ofstr << *it << endl;
                  i =0;
              }else{
                  ofstr << *it << "     ";
                  i++;
              }
          }
          ofstr << "\t\t ]" << endl;
          ofstr << "\t\t}" << endl;
      }
      if(!ifs.getCoordIndex().empty()){
          ofstr << "\t\tcoordIndex [" << endl;
          int i=0;
          for(std::vector<int>::iterator it=ifs.getCoordIndex().begin(); it != ifs.getCoordIndex().end(); it++,i++){
    //          ofstr.precision(4);
              if(i%4==0) ofstr << "\t\t";
              if(*it==-1){
                  ofstr << *it << endl;
                  i =0;
              }else {
                  ofstr << *it << "\t";
              }
          }
          ofstr << "\t\t ]" << endl;
      }
      ofstr << "\t\tcolorPerVertex ";
      if(ifs.getColorPerVertex())
          ofstr << "TRUE" << endl;
      else ofstr << "FALSE" << endl;
      if(!ifs.getColor().empty()){
          ofstr << "\t\tcolor Color {" << endl;
          ofstr << "\t\t point [" << endl;
          int i = 0;
          for(std::vector<float>::iterator it=ifs.getColor().begin(); it != ifs.getColor().end(); it++){
              ofstr.precision(6);
              ofstr.setf(ios::fixed);
              ofstr.setf(ios::showpoint);
              if(i%3==0) ofstr << "\t\t";
              if(i%3==2){
                  ofstr << *it << endl;
                  i =0;
              }else{
                  ofstr << *it << "     ";
                  i++;
              }
          }
          ofstr << "\t\t ]" << endl;
          ofstr << "\t\t}" << endl;
      }
      if(!ifs.getColorIndex().empty()){
          ofstr << "\t\tcolorIndex [" << endl;
          int i=0;
          for(std::vector<int>::iterator it=ifs.getColorIndex().begin(); it != ifs.getColorIndex().end(); it++,i++){
              //          ofstr.precision(4);
              if(i%4==0) ofstr << "\t\t";
              if(*it==-1){
                  ofstr << *it << endl;
                  i =0;
              }else {
                  ofstr << *it << "\t";
              }
          }
          ofstr << "\t\t ]" << endl;
      }
      ofstr << "\t\tnormalPerVertex ";
      if(ifs.getNormalPerVertex())
          ofstr << "TRUE" << endl;
      else ofstr << "FALSE" << endl;
      if(!ifs.getNormal().empty()){
          ofstr << "\t\tnormal Normal {" << endl;
          ofstr << "\t\t vector [" << endl;
          int i = 0;
          for(std::vector<float>::iterator it=ifs.getNormal().begin(); it != ifs.getNormal().end(); it++){
              ofstr.precision(6);
              ofstr.setf(ios::fixed);
              ofstr.setf(ios::showpoint);
              if(i%3==0) ofstr << "\t\t";
              if(i%3==2){
                  ofstr << *it << endl;
                  i =0;
              }else{
                  ofstr << *it << "     ";
                  i++;
              }
          }
          ofstr << "\t\t ]" << endl;
          ofstr << "\t\t}" << endl;
      }
      if(!ifs.getNormalIndex().empty()){
          ofstr << "\t\tnormalIndex [" << endl;
          int i=0;
          for(std::vector<int>::iterator it=ifs.getNormalIndex().begin(); it != ifs.getNormalIndex().end(); it++,i++){
              //          ofstr.precision(4);
              if(i%4==0) ofstr << "\t\t";
              if(*it==-1){
                  ofstr << *it << endl;
                  i =0;
              }else {
                  ofstr << *it << "\t";
              }
          }
          ofstr << "\t\t]" << endl;
      }
      
      if(!ifs.getTexCoord().empty()){
          ofstr << "\t\ttexCoord TextureCoordinate {" << endl;
          ofstr << "\t\t point [" << endl;
          int i = 0;
          for(std::vector<float>::iterator it=ifs.getTexCoord().begin(); it != ifs.getTexCoord().end(); it++){
              ofstr.precision(6);
              ofstr.setf(ios::fixed);
              ofstr.setf(ios::showpoint);
              if(i%3==0) ofstr << "\t\t";
              if(i%3==2){
                  ofstr << *it << endl;
                  i =0;
              }else{
                  ofstr << *it << "     ";
                  i++;
              }
          }
          ofstr << "\t\t ]" << endl;
          ofstr << "\t\t}" << endl;
      }
      if(!ifs.getTexCoordIndex().empty()){
          ofstr << "\t\tcolorIndex [" << endl;
          int i=0;
          for(std::vector<int>::iterator it=ifs.getTexCoordIndex().begin(); it != ifs.getTexCoordIndex().end(); it++,i++){
              //          ofstr.precision(4);
              if(i%4==0) ofstr << "\t\t";
              if(*it==-1){
                  ofstr << *it << endl;
                  i =0;
              }else {
                  ofstr << *it << "\t";
              }
          }
          ofstr << "\t\t]" << endl;
      }
      ofstr << "\t\tccw ";
      if(ifs.getCcw())
          ofstr << "TRUE" << endl;
      else ofstr << "FALSE" << endl;
      ofstr << "\t\tconvex ";
      if(ifs.getConvex())
          ofstr << "TRUE" << endl;
      else ofstr << "FALSE" << endl;
      ofstr << "\t\tcreaseAngle ";
      ofstr << ifs.getCreaseangle() << endl;
      ofstr << "\t}" << endl;
      ofstr << "}" << endl;
      ofstr.close();
      success = true;
  }
  return success;
}


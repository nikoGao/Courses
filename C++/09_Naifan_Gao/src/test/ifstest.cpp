// AUTHOR : Your Name <your_email@brown.edu>
//
// ifstest.cpp
//

#include <string>
#include <iostream>

using namespace std;

#include <ifs/Ifs.hpp>
#include <ifs/IfsLoader.hpp>
#include <ifs/IfsSaver.hpp>
#include <ifs/IfsWrlLoader.hpp>
#include <ifs/IfsWrlSaver.hpp>

class Data {
public:
  bool   debug;
  bool   removeNormal;
  bool   removeColor;
  bool   removeTexCoord;
  string inFile;
  string outFile;
public:
  Data():
    debug(false),
    removeNormal(false),
    removeColor(false),
    removeTexCoord(false),
    inFile(""),
    outFile("") {
  }
};

const char* tv(bool value)        { return (value)?"true":"false";                 }

void options(Data& D) {
  cerr << "   -d|-debug               [" << tv(D.debug)          << "]" << endl;
  cerr << "  -rn|-removeNormal        [" << tv(D.removeNormal)   << "]" << endl;
  cerr << "  -rc|-removeColor         [" << tv(D.removeColor)    << "]" << endl;
  cerr << "  -rt|-removeTexCoord      [" << tv(D.removeTexCoord) << "]" << endl;
//  cerr << "   -i|-inputFile           [" << "inputFile.wrl" << "]" << endl;
//  cerr << "   -o|-outputFile          [" << "outputFile.wrl" << "]" << endl;
}

void usage(Data& D) {
  cerr << "USAGE: ifstest [options] inFile outFile" << endl;
  cerr << "   -h|-help" << endl;
  options(D);
  cerr << endl;
  exit(0);
}

void error(const char *msg) {
  cerr << "ERROR: ifstest | " << ((msg)?msg:"") << endl;
  exit(0);
}
//////////////////////////////////////////////////////////////////////
char* command[] = {"ifsTest", "-d", "/Users/niko/Documents/Courses/C++/IfsViewer-data/armadillo-mat-npf.wrl", "test.wrl"};
//////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {

  Data D;
    argv = command;
    argc = 4;
  if(argc==1) usage(D);

  for(int i=1;i<argc;i++) {
    /* TODO */
      if(string(argv[i])=="-d"||string(argv[i])=="-debug"){
          D.debug=true;
      }
      else if(string(argv[i])=="-rn"||string(argv[i])=="-removeNormal"){
          D.removeNormal=true;
      }
      else if(string(argv[i])=="-rc"||string(argv[i])=="-removeColor"){
          D.removeColor=true;
      }
      else if(string(argv[i])=="-rt"||string(argv[i])=="-removeTexCoord"){
          D.removeTexCoord=true;
      }
      else if(string(argv[i])=="-h"||string(argv[i])=="-help"){
          usage(D);
      }
      else if(argv[i][0]=='-'){
          usage(D);
      }
      else if(D.inFile==""){
          D.inFile=string(argv[i]);
      }else if(D.outFile==""){
          D.outFile=string(argv[i]);
      }
      
  }

  if(D.inFile =="") error("no inFile");
  if(D.outFile=="") error("no outFile");

  // if command run without arguments, print the usage message and exit

  // if errors are detected in the argument list, print an error
  // message and exit

  bool success = false;

  //////////////////////////////////////////////////////////////////////
  // create loader and saver and register IfsLoaders and IfsSavers

  // TODO
    IfsLoader loader = IfsLoader();
    IfsSaver saver = IfsSaver();
    IfsWrlLoader* wrlLoader =new IfsWrlLoader();
    IfsWrlSaver* wrlSaver = new IfsWrlSaver();
    loader.registerLoader(wrlLoader);
    saver.registerSaver(wrlSaver);

  //////////////////////////////////////////////////////////////////////
  // open input file and load Ifs

  Ifs ifs;

  // TODO

  // remember to set success to true or false

  if(D.debug) {
      success = loader.load(D.inFile.c_str(), ifs);
    // PRINT SOME INFO ABOUT IFS OR ERROR MESSAGE
  }
    try{
        if(success==false) throw -1;
        else cerr << "Success" << endl;
    }catch(int e){
        error("Loading File failed, please check file;");
    }

  //////////////////////////////////////////////////////////////////////
  // process
    if(success){
      if(D.removeNormal) {
        // TODO
          ifs.clearNormal();
          ifs.clearNormalIndex();
          ifs.setNormalPerVertex(true);
      }
      if(D.removeColor) {
        // TODO
          ifs.clearColor();
          ifs.clearColorIndex();
          ifs.setColorPerVertex(true);
      }
      if(D.removeTexCoord) {
        // TODO
          ifs.clearTexCoord();
          ifs.clearTexCoordIndex();
      }

      //////////////////////////////////////////////////////////////////////
      // save modified Ifs to output file

      // TODO

      if(D.debug) {
        // PRINT SOME INFO ABOUT SAVED IFS OR ERROR MESSAGE
          success = saver.save(D.outFile.c_str(), ifs);
      }
    }
    try{
        if(success==false) throw -1;
    }catch(int e){
        error("Can not save file");
    }

  //////////////////////////////////////////////////////////////////////

  return 0;
}

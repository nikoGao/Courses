// AUTHOR : Your Name <your_email@brown.edu>
//
// IfsSaver.cpp
//

#include "IfsSaver.hpp"
#include <fstream>

bool IfsSaver::save(const char* filename, Ifs& ifs) {
  bool success = false;
  if(filename!=(const char*)0) {
    // TODO
      ofstream os(filename);
      if(!os) return success;
      string const file_name = string(filename);
      unsigned long i= file_name.find('.');
      if(i==string::npos) return success;
      string extension = file_name.substr(i+1,3);
      if(_registry[extension]->save(filename, ifs))
          success = true;
  }
  return success;
}

void IfsSaver::registerSaver(Saver* saver) {
  if(saver!=(Saver*)0) {
    // TODO
      string extension = saver->ext();
      pair<string, Saver*> p(extension, saver);
      _registry.insert(p);
  }
}

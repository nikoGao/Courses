// AUTHOR : Naifan Gao <naifan_gao@brown.edu>
//
// IfsLoader
//

#include "IfsLoader.hpp"
#include <fstream>

bool IfsLoader::load(const char* filename, Ifs& ifs) {
  bool success = false;
  if(filename!=(const char*)0) {
    // TODO
      ifstream is(filename);
      if(!is) return success;
      string const file_name = string(filename);
      unsigned long i= file_name.find('.');
      if(i==string::npos) return success;
      string extension = file_name.substr(i+1,3);
      if(_registry[extension]->load(filename, ifs))
          success=true;
  }
  return success;
}

void IfsLoader::registerLoader(Loader* loader) {
  if(loader!=(Loader*)0) {
    // TODO
      string extension = loader->ext();
      pair<string, Loader*> p(extension, loader);
      _registry.insert(p);
  }
}

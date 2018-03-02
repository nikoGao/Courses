set(NAME ifs)

set(HEADERS
  Ifs.hpp
  IfsWrlLoader.hpp
  IfsWrlSaver.hpp
  IfsLoader.hpp
  IfsSaver.hpp
  Tokenizer.hpp
) # HEADERS    

set(SOURCES
  Ifs.cpp
  IfsWrlLoader.cpp
  IfsWrlSaver.cpp
  IfsLoader.cpp
  IfsSaver.cpp
  Tokenizer.cpp
) # SOURCES

qt5_wrap_ui(FORMS
) # FORMS

qt5_add_resources(ASSETS
) # ASSETS

add_library(${NAME}
    ${HEADERS}
    ${SOURCES}
    ${FORMS}
    ${ASSETS}
) # add_library

target_compile_features(${NAME} PRIVATE cxx_lambdas)

target_link_libraries(${NAME} ${LIB_LIST})


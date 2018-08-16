#pragma once

#include "algorithm.h"

namespace SanBruno {

  class Function {
  };

  enum DataType {
    DATA_TYPE_ARRAY,
    DATA_TYPE_CUSTOM
  };

  class Data {
  };

  class Context {
  public:

    Data* arrayType(const int width) {
      return nullptr;
    }

    Function* newFunction(const std::string& name,
                          const std::map<std::string, Data*>& inputs,
                          const std::map<std::string, Data*>& outputs) {
      return nullptr;
    }
  };

}

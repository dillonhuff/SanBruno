#pragma once

#include "algorithm.h"

namespace SanBruno {

  class Value {
  };

  class Function {
  public:
    Value* addFunctionCall(const std::string& str);

    Value* getValue(const std::string& name) {
      return nullptr;
    }

    Value* addSlice(const int end, const int start, Value* v) {
      return nullptr;
    }

    Value* addEquals(const Value* a, const Value* b) {
      return nullptr;
    }

    Value* addCase(const Value* res, const Value* ifTrue, const Value* ifFalse) {
      return nullptr;
    }

    Value* addConstant(const int bitWidth, const int Value) {
      return nullptr;
    }

  };

  enum DataType {
    DATA_TYPE_ARRAY,
    DATA_TYPE_CUSTOM
  };

  class Data {
  };

  class Context {

    std::map<std::string, Function*> functions;
  public:

    Data* arrayType(const int width) {
      return nullptr;
    }

    Function* newFunction(const std::string& name,
                          const std::map<std::string, Data*>& inputs,
                          const std::map<std::string, Data*>& outputs) {
      auto f = new Function();
      functions.insert({name, f});
      return f;
    }

    ~Context() {
      for (auto f : functions) {
        delete f.second;
      }
    }
  };

}

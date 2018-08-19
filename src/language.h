#pragma once

#include "algorithm.h"

#include <fstream>

using namespace dbhc;

namespace SanBruno {

  static inline
  std::string tab(const int indentLevel) {
    std::string ind = "";
    for (int i = 0; i < indentLevel; i++) {
      ind += "\t";
    }
    return ind;
  }

  class Value {
  };

  enum StatementType {
    STATEMENT_TYPE_FUNCTION_CALL,
    STATEMENT_TYPE_CASE,
    STATEMENT_TYPE_OPERATOR,
    STATEMENT_TYPE_RETURN,
  };

  class Statement {
  public:

    std::string toString(const int indentLevel) const {
      return tab(indentLevel) + "STATEMENT";
    }

    virtual StatementType type() const = 0;

    virtual ~Statement() {}
  };

  class Case : public Statement {
  public:
    virtual StatementType type() const {
      return STATEMENT_TYPE_CASE;
    }
  };

  
  class Operator : public Statement {
  public:
    virtual StatementType type() const {
      return STATEMENT_TYPE_OPERATOR;
    }
  };

  class FunctionCall : public Statement {
  public:
    virtual StatementType type() const {
      return STATEMENT_TYPE_FUNCTION_CALL;
    }
  };

  class ReturnStmt : public Statement {
  public:
    virtual StatementType type() const {
      return STATEMENT_TYPE_RETURN;
    }
  };
  
  class Function {
    std::string name;
    std::vector<Statement*> statements;

  public:

    Function(const std::string& name_) : name(name_) {}

    std::string getName() const {
      return name;
    }

    std::vector<Statement*> getStatements() const {
      return statements;
    }

    Value* addFunctionCall(const std::string& str);

    Value* getValue(const std::string& name) {
      return nullptr;
    }

    Value* addSlice(const int end, const int start, Value* v) {
      statements.push_back(new FunctionCall());
      return nullptr;
    }

    Value* addEquals(const Value* a, const Value* b) {
      statements.push_back(new FunctionCall());
      return nullptr;
    }

    Value* addCase(const Value* res, const Value* ifTrue, const Value* ifFalse) {
      statements.push_back(new Case());
      return nullptr;
    }

    Value* addConstant(const int bitWidth, const int Value) {
      return nullptr;
    }

    void setReturn(const std::string& returnName, const Value* value) {
      statements.push_back(new ReturnStmt());
    }

    ~Function() {
      for (auto stmt : statements) {
        delete stmt;
      }
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
      auto f = new Function(name);
      functions.insert({name, f});
      return f;
    }

    // Synthesize by unfolding the entire compute graph
    void synthesizeNaive(const std::string& functionName) {


      Function* f = map_find(functionName, functions);

      std::string verilogFile = f->getName() + ".v";
      std::ofstream of(verilogFile);

      of << "module " << f->getName() << "();" << std::endl;

      for (auto stmt : f->getStatements()) {
        std::cout << stmt->toString(0) << std::endl;
      }

      of << "endmodule";
        
      of.close();

    }

    ~Context() {
      for (auto f : functions) {
        delete f.second;
      }
    }
  };

}

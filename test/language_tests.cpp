#include "catch.hpp"

#include "language.h"

using namespace std;

namespace SanBruno {

  bool runCmd(const std::string& cmd) {
    int res = system(cmd.c_str());
    return res == 0;
  }

  bool runVerilatorTB(const std::string& moduleName) {
    string verilogFileName = moduleName + ".v";
    string tbName = "./test/tbs/" + moduleName + "_tb.cpp";
    string verilatorStr = "verilator --cc " + verilogFileName + " --exe " + tbName + " --top-module " + moduleName;

    cout << "Verilator str = " << verilatorStr << endl;

    bool verilatorCompiled = runCmd(verilatorStr);

    if (!verilatorCompiled) {
      return false;
    }

    string makeTbStr = "make -C obj_dir -j -f V" + moduleName + ".mk V" + moduleName;
    bool makeRes = runCmd(makeTbStr);

    if (!makeRes) {
      return false;
    }

    string runVerilatorStr = "./obj_dir/V" + moduleName;
    bool verilatorRan = runCmd(runVerilatorStr);
    
    return verilatorRan;
  }

  TEST_CASE("Express 32 bit add sign bit computation") {
    Context c;
    Function* p = c.newFunction("float_add_32_sign_bit",
                                {{"a", c.arrayType(32)},
                                    {"b",c.arrayType(32)}},
                                {{"sign_bit", c.arrayType(1)}});

    REQUIRE(p != nullptr);

    // Now: Create function definition
    Value* aSgnBit = p->addSlice(31, 31, p->getValue("a"));
    Value* bSgnBit = p->addSlice(31, 31, p->getValue("b"));

    Value* res = p->addEquals(aSgnBit, bSgnBit);

    Value* resSignBit =
      p->addCase(res,
                 p->addConstant(1, 1),
                 p->addConstant(1, 0));

    p->setReturn("sign_bit", resSignBit);

    REQUIRE(p->getStatements().size() == 5);

    // Synthesize this function
    c.synthesizeNaive("float_add_32_sign_bit");

    REQUIRE(runVerilatorTB("float_add_32_sign_bit"));
  }

}

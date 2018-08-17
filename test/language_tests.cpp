#include "catch.hpp"

#include "language.h"

namespace SanBruno {

  TEST_CASE("Express 32 bit add") {
    Context c;
    Function* p = c.newFunction("float_add_32",
                                {{"a", c.arrayType(32)},
                                    {"b",c.arrayType(32)}},
                                {{"result", c.arrayType(32)}});

    REQUIRE(p != nullptr);

    // Now: Create function definition and test it
    Value* aSgnBit = p->addSlice(31, 31, p->getValue("a"));
    Value* bSgnBit = p->addSlice(31, 31, p->getValue("b"));

    Value* res = p->addEquals(aSgnBit, bSgnBit);

    Value* resSignBit =
      p->addCase(res,
                 p->addConstant(1, 1),
                 p->addConstant(1, 0));
  }

}

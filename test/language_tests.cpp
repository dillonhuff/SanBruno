#include "catch.hpp"

#include "language.h"

namespace SanBruno {

  TEST_CASE("Express 32 bit floating point multiply") {
    Context c;
    Function* p = c.newFunction("float_add_32",
                                {{"a", c.arrayType(32)},
                                    {"b",c.arrayType(32)}},
                                {{"result", c.arrayType(32)}});

    

    
  }

}

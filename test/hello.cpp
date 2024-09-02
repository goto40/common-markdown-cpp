#include "common_markdown_cpp/version.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

TEST_CASE("hello_world", "[hello]") {
  std::cout << "common_markdown_cpp " << common_markdown_cpp::VERSION << " "
            << common_markdown_cpp::VERSION_SHORT << " unittests\n";
  REQUIRE(true);
}

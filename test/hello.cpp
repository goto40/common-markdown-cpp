#include "common_markdown_cpp/block_parser.hpp"
#include "common_markdown_cpp/version.h"
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

TEST_CASE("hello_world", "[hello]") {
  std::cout << "common_markdown_cpp " << common_markdown_cpp::VERSION << " "
            << common_markdown_cpp::VERSION_SHORT << " unittests\n";
  REQUIRE(true);
}

TEST_CASE("paragraphs", "[simple parser tests]") {
  using namespace common_markdown_cpp;

  std::string text = R"(Hello
  This is Paragraph1
  ...

  And this is Para2
  with two lines

  And this Para3

  and this P4)";

  std::istringstream in{text};
  std::string line;
  std::shared_ptr<Block> doc = std::make_shared<Block>();
  while (std::getline(in, line)) {
    add_next_line(doc, line);
  }

  print(std::cout, doc);

  REQUIRE(doc->blocks.size() == 4);
  CHECK(doc->blocks.at(0)->text.size() == 3);
  CHECK(doc->blocks.at(1)->text.size() == 2);
  CHECK(doc->blocks.at(2)->text.size() == 1);
  CHECK(doc->blocks.at(3)->text.size() == 1);
}

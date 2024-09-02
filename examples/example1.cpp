#include "common_markdown_cpp/version.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

int main(int argc, const char **argv) {
  try {
    if (argc != 2) {
      std::cout << "common_markdown_cpp " << common_markdown_cpp::VERSION
                << "\n";
      std::cout << "usage " << argv[0] << " <filename>\n";
    } else {
      std::ifstream f(argv[1]);
      assert(f && "problem opening file");
      std::string source((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());
      std::cout << source << "\n";
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
  }
}

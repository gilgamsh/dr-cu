#include <cxxopts.hpp>
#include <database/database.hpp>
#include <iostream>
#include <string>


void run(std::string lef_file, std::string def_file) {
  db.init();
}

int main(int argc, char *argv[]) {
  // Parse command line arguments
  cxxopts::Options options("io_test", "test the parse of lef and def file");
  // clang-format off
    options.add_options()
            ("h,help", "Print help")
            ("lef", "lef file", cxxopts::value<std::string>())
            ("def", "def file", cxxopts::value<std::string>());
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (!result.count("lef") || !result.count("def")) {
    std::cout << "Error: lef and def file must be specified" << std::endl;
    exit(1);
  }

  std::string lef_file = result["lef"].as<std::string>();
  std::string def_file = result["def"].as<std::string>();

  run(lef_file, def_file);
}
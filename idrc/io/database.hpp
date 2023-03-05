#pragma once

#include "rsyn/phy/util/DefDescriptors.h"
#include "rsyn/phy/util/LefDescriptors.h"
#include <memory>
#include <string>
#include <vector>
namespace io {

class database {
public:
  std::string lef_filename;
  std::string def_filename;

  LefDscp lef_descriptor;
  DefDscp def_descriptor;

  void read();
  void parse_lef();
  void parse_def();
};

} // namespace io
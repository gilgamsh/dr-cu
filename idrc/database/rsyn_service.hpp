#pragma once

#include <rsyn/session/Session.h>
#define RSYN_NO_GUI
#include <rsyn/core/Rsyn.h>
#include <rsyn/phy/PhysicalService.h>

namespace database {

class rsyn_service {
public:
  Rsyn::PhysicalService *physical_service_;
  Rsyn::PhysicalDesign physical_design_;
  Rsyn::Design design_;
  Rsyn::Module module_;

  void init();
  
};

} // namespace io
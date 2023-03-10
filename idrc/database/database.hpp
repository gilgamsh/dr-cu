#pragma once

#include <database/netlist.hpp>
#include <database/rsyn_service.hpp>

namespace database {

class database : public netlist{
public:
  database() = default;


  void init();


private:
  std::string lef_file_;
  std::string def_file_;

  rsyn_service rsyn_service_;

};

} // namespace database

inline database::database db;

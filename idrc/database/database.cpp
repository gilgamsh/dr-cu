#include <database/database.hpp>


namespace database {

void database::init(){
    
    rsyn_service_.init();
    netlist::init(rsyn_service_);
  };


}
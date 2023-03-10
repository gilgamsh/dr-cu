#include <database/rsyn_service.hpp>

namespace database {

void rsyn_service::init() {
  Rsyn::Session session;

  physical_service_ = session.getService("rsyn.physical");
  physical_design_ = physical_service_->getPhysicalDesign();
  design_ = session.getDesign();
  module_ = design_.getTopModule();
}

} // namespace database
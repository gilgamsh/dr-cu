#include "database.hpp"

namespace io {

void database::read() {
  parse_lef();
  parse_def();
}

}
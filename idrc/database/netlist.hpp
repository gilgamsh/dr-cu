#pragma once

#include <database/box_on_layer.hpp>
#include <database/rsyn_service.hpp>
#include <string_view>

namespace database {

class net {
public:
  net() = default;
  net(rsyn_service &rsyn_service, Rsyn::Net rsyn_net) {
    init(rsyn_service, rsyn_net);
  }

  Rsyn::Net rsyn_net_;
  const std::string_view get_name() const { return rsyn_net_.getName(); }

  vector<Rsyn::Pin> rsyn_pins_;
  vector<vector<box_on_layer>> pin_boxes_;
  std::size_t get_num_pins() const { return rsyn_pins_.size(); }

  vector<DefWireSegmentDscp> defWireSegments_;
  vector<box_on_layer> wire_boxes_;

  void init(rsyn_service &rsyn_service, Rsyn::Net rsyn_net) {
    rsyn_net_ = rsyn_net;

    // init rsyn_pins_
    rsyn_pins_.reserve(rsyn_net.getNumPins());
    pin_boxes_.reserve(rsyn_net.getNumPins());
    const auto &physical_design = rsyn_service.physical_design_;
    const auto lib_dbu = physical_design.getDatabaseUnits(Rsyn::LIBRARY_DBU);
    for (auto rsyn_pin : rsyn_net.allPins()) {
      rsyn_pins_.emplace_back(rsyn_pin);
      // init pin_boxes_
      pin_boxes_.emplace_back();
    }

    Rsyn::PhysicalNet physical_net = physical_design.getPhysicalNet(rsyn_net);
    const auto &routing = physical_net.getRouting();
    std::cout<< "net name = " << rsyn_net.getName();
    std::cout << "routing.size() = " << routing.allWires().size() << std::endl;
  }
};

class netlist {
public:
  vector<net> nets;

  void init(rsyn_service &rsyn_service) {
    nets.clear();
    nets.reserve(rsyn_service.design_.getNumNets());
    int numPins = 0;
    for (auto net : rsyn_service.module_.allNets()) {
      auto use = net.getUse();
      if (use == Rsyn::POWER || use == Rsyn::GROUND)
        continue;

      nets.emplace_back(rsyn_service, net);
    }
  };
};

} // namespace database
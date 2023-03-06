#pragma once

#include <Rsyn/PhysicalDesign>
#include <Rsyn/Session>
#include <rsyn/io/parser/lef_def/DEFControlParser.h>
#include <rsyn/io/parser/lef_def/LEFControlParser.h>

namespace Rsyn {

class rsyn_reader : public Reader {
public:
  rsyn_reader() = default;

  virtual bool load(const Json &params) override {
    Rsyn::Session session;

    std::string path = params.value("path", "");

    if (!params.count("lefFile")) {
      std::cout << "[ERROR] LEF file not specified...\n";
      return false;
    } // end if
    lef_file_ = session.findFile(params.value("lefFile", ""), path);

    if (!params.count("defFile")) {
      std::cout << "[ERROR] DEF file not specified...\n";
      return false;
    } // end if
    def_file_ = session.findFile(params.value("defFile", ""), path);

    parsing_flow();
    return true;
  };

private:
  Session session;

  std::string lef_file_;
  std::string def_file_;
  LefDscp lef_descriptor_;
  DefDscp def_descriptor_;

  void parse_lef_file() {
    LEFControlParser lef_parser;
    lef_parser.parseLEF(lef_file_, lef_descriptor_);
  };

  void parse_def_file() {
    DEFControlParser def_parser;
    def_parser.parseDEF(def_file_, def_descriptor_);
  };

  void parsing_flow() {
    parse_lef_file();
    parse_def_file();
    populate_design();
  };

  void populate_design() {
    Rsyn::Design design = session.getDesign();
    Reader::populateRsyn(lef_descriptor_, def_descriptor_, design);

    Rsyn::Json physicalDesignConfiguration;
    physicalDesignConfiguration["clsEnableMergeRectangles"] = false;
    physicalDesignConfiguration["clsEnableNetPinBoundaries"] = true;
    physicalDesignConfiguration["clsEnableRowSegments"] = true;
    session.startService("rsyn.physical", physicalDesignConfiguration);
    
    Rsyn::PhysicalDesign physicalDesign = session.getPhysicalDesign();
    physicalDesign.loadLibrary(lef_descriptor_);
    physicalDesign.loadDesign(def_descriptor_);
    physicalDesign.updateAllNetBounds(false);
  };
};

} // namespace Rsyn
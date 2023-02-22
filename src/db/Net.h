#pragma once

#include "RsynService.h"
#include "GridTopo.h"

namespace db {

class NetBase {
public:
    ~NetBase();

    int idx;
    Rsyn::Net rsynNet;
    const std::string& getName() const { return rsynNet.getName(); }

    // pins
    vector<Rsyn::Pin> rsynPins;
    vector<vector<BoxOnLayer>> pinAccessBoxes;  // (pinIdx, accessBoxIdx) -> BoxOnLayer
    unsigned numOfPins() const noexcept { return pinAccessBoxes.size(); }
    BoxOnLayer getMaxAccessBox(int pinIdx) const;

    // route guides
    vector<BoxOnLayer> routeGuides;
    vector<GridBoxOnLayer> gridRouteGuides;

    // on-grid route result
    vector<std::shared_ptr<GridSteiner>> gridTopo;
    vector<std::shared_ptr<GridSteiner>> gridTopo_copy;
    void postOrderVisitGridTopo(const std::function<void(std::shared_ptr<GridSteiner>)>& visit) const;
    void postOrderVisitGridTopo_copy(const std::function<void(std::shared_ptr<GridSteiner>)>& visit) const;


    // print
    void printBasics(ostream& os) const;
    void printResult(ostream& os) const;
    void print(ostream& os = std::cout) const {
        printBasics(os);
        printResult(os);
    };
    void printOldResult(ostream& os) const;

};

class Net : public NetBase {
public:
    Net(int i, Rsyn::Net net, RsynService& rsynService);

    // more route guide information
    vector<int> routeGuideVios;
    RTrees routeGuideRTrees;
    vector<int> routeGuideVios_copy;
    RTrees routeGuideRTrees_copy;

    // for initialization
    void initPinAccessBoxes(Rsyn::Pin rsynPin, RsynService& rsynService, vector<BoxOnLayer>& accessBoxes, const DBU libDBU);
    static void getPinAccessBoxes(Rsyn::PhysicalPort phPort, vector<BoxOnLayer>& accessBoxes);
    static void getPinAccessBoxes(Rsyn::PhysicalLibraryPin phLibPin,
                                  Rsyn::PhysicalCell phCell,
                                  vector<BoxOnLayer>& accessBoxes,
                                  const DBUxy& origin);

    // final route result
    vector<DefWireSegmentDscp> defWireSegments;
    void clearPostRouteResult();
    void clearResult();
    void stash();
    void reset();



    void printFinalResult(ostream& os) const {
        os << "Net " << getName() << ":\n";
        os << "  # of wire segments: " << defWireSegments.size() << "\n";
        for (const auto& seg : defWireSegments) {
            os << "  layer: " << seg.clsLayerName << " width: " << seg.clsRoutedWidth << "\n";
            for (const auto& pt : seg.clsRoutingPoints) {
               os << "clsPos:" << pt.clsPos << " clsRect:" << pt.clsRect <<  " clsVia:" << pt.clsViaName << "\n";
            }
        }
    };
};

class NetList {
public:
    vector<Net> nets;

    void init(RsynService& rsynService);
    void writeNetTopo(const std::string& filename);
    void printFinalResult(ostream& os= std::cout) const {
        for (const auto& net : nets) {
            net.printFinalResult(os);
        }
    };
};

}  // namespace db

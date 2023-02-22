#pragma once

#include "db/Database.h"
#include "single_net/SingleNetRouter.h"

class Router {
public:
    void run();

private:
    int iter = 0;
    vector<float> _netsCost;
    vector<db::RouteStatus> allNetStatus;
    vector<int> layersToGrids; // each layer has how many grids 
    vector<int> layersToGridsInUse; // each layer has how many grids in use
    using Coord = std::tuple<int, int, int>;
    using Edge  = std::pair<Coord, Coord>;
    vector<vector<Edge>> nets;


    vector<int> getNetsToRoute();
    void ripup(const vector<int>& netsToRoute);
    void updateCost(const vector<int>& netsToRoute);
    void route(const vector<int>& netsToRoute);
    void finish();
    void unfinish();

    void printStat(bool major = false);
    void recordNetsToRoute_before(const vector<int>& netsToRoute);
    void recordNetsToRoute_after(const vector<int>& netsToRoute,int iter=0);

    void init_layersToGrids() {
        auto nlayers = database.layers.size();
        layersToGrids.resize(nlayers);
        layersToGridsInUse.resize(nlayers);
        for (int i = 0; i < nlayers; i++) {
            layersToGrids[i] = database.layers[i].numGridPoints();
            layersToGridsInUse[i] = 0;
        }
    };
};

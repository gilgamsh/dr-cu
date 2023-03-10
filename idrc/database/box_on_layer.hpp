#pragma once

#include <rsyn/util/Bounds.h>
#include <rsyn/util/dbu.h>
#include <rsyn/phy/PhysicalService.h>

#include <utils/utils.h>

namespace database {

using box = utils::BoxT<DBU>;

class box_on_layer : public box{
public:
    int layer_idx;

    template<typename... Args>
    box_on_layer(int layer_idx, Args&&... args) : box(std::forward<Args>(args)...), layer_idx(layer_idx) {}

    template<typename... Args>
    void set(int layer_idx, Args&&... args) {
        box::Set(std::forward<Args>(args)...);
        this->layer_idx = layer_idx;
    }

    bool is_connected(const box_on_layer& other) const {
        return layer_idx == other.layer_idx && box::HasIntersectWith(other);
    }

    bool is_connected_through_via(const box_on_layer& other) const {
        return std::abs(layer_idx - other.layer_idx)<=1 && box::HasIntersectWith(other);
    }

};

inline box get_box_from_rsyn_bounds(const Bounds& bounds) {
    return {bounds.getLower().x, bounds.getLower().y, bounds.getUpper().x, bounds.getUpper().y};
}

inline box get_box_from_rsyn_geometries(const std::vector<Rsyn::PhysicalViaGeometry>& geometries) {
    box result;
    for (const auto& geometry : geometries) {
        result = result.UnionWith(get_box_from_rsyn_bounds(geometry.getBounds()));
    }
    return result;
}

} // namespace database
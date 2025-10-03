#pragma once

#include <cstdint>

#include "order_type.hpp"
#include "side.hpp"

struct Order {
    std::uint64_t id_;
    double price_;
    double quantity_;
    Side side;
    OrderType type;
    OrderTIF tif;
};

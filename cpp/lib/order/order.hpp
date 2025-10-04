#pragma once

#include <cstdint>

#include "common.hpp"

struct Order {
    std::uint64_t id_;
    Price price_;
    Size size_;
    Side side_;
    OrderType type_;
    OrderTIF tif_;
};

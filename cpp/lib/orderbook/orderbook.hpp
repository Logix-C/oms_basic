#pragma once

#include <vector>

#include <order.hpp>

struct Orderbook {

private:
    std::vector<std::pair<double, std::vector<Order>>> bids_;
    std::vector<std::pair<double, std::vector<Order>>> asks_;
};
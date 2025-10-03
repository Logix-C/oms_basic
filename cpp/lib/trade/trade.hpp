#pragma once

#include <cstdint>

struct TradeInfo {
    std::uint64_t id_;
    double price_;
    double quantity_;
};

struct Trade {
    TradeInfo bid_;
    TradeInfo ask_;
};

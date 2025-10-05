#pragma once

#include <cstdint>

#include "common.hpp"

namespace oms {
    struct Trade {
        std::uint64_t id_;
        common::Price price_;
        common::Size size_;
        common::Side side_;
    };

    using Trades = std::vector<Trade>;
}

// struct TradeInfo {
//     std::uint64_t id_;
//     Price price_;
//     Size size_;
//     Side side_;
// };
//
// struct Trade {
//     TradeInfo bid_;
//     TradeInfo ask_;
// };
//
// using Trades = std::vector<Trade>;

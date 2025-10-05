#pragma once

#include <ostream>

#include "decimal.hpp"

namespace oms::common {
    enum class OrderType {
        LIMIT = 0,
        MARKET = 1
    };

    enum class OrderTIF {
        GTC = 0,
        FAK = 1,
        FOK = 2,
        DAY = 3
    };

    enum class Side {
        BID = 0,
        ASK = 1
    };

    inline std::ostream& operator<<(std::ostream& os, OrderType type) {
        switch (type) {
        case OrderType::LIMIT:  return os << "LIMIT";
        case OrderType::MARKET: return os << "MARKET";
        default:                return os << "UNKNOWN_ORDER_TYPE";
        }
    }

    inline std::ostream& operator<<(std::ostream& os, OrderTIF tif) {
        switch (tif) {
        case OrderTIF::GTC: return os << "GTC";
        case OrderTIF::FAK: return os << "FAK";
        case OrderTIF::FOK: return os << "FOK";
        case OrderTIF::DAY: return os << "DAY";
        default:            return os << "UNKNOWN_TIF";
        }
    }

    inline std::ostream& operator<<(std::ostream& os, Side side) {
        switch (side) {
        case Side::BID: return os << "BID";
        case Side::ASK: return os << "ASK";
        default:        return os << "UNKNOWN_SIDE";
        }
    }

    using Price = utils::Decimal<1'000'000, 1>;

    using Size = utils::Decimal<1'000'000, 1>;

    using TimePoint = std::chrono::steady_clock::time_point;
}

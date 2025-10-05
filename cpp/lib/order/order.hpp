#pragma once

#include <cstdint>
#include <optional>

#include "common.hpp"

namespace oms {
    struct Order {
        std::uint64_t id_;
        common::Price price_;
        common::Size size_;
        common::Side side_;
        common::OrderType type_;
        common::OrderTIF tif_;

        common::Size filled_size_;

        common::TimePoint created_at_;
        std::optional<common::TimePoint> last_updated_;
        std::optional<common::TimePoint> expires_after_;

        std::optional<common::TimePoint> exchange_timestamp_;
    };
}

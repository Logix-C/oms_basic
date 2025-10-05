#pragma once

#include <unordered_map>

#include <order.hpp>
#include <trade.hpp>
#include <flat_map.hpp>

namespace oms {
    struct Orderbook {
        Orderbook();
        Orderbook(const Orderbook& other);
        Orderbook& operator=(const Orderbook& other);
        Orderbook(Orderbook&& other) noexcept;
        Orderbook& operator=(Orderbook&& other) noexcept;

        Trades add_order(Order order);
        void cancel_order(uint64_t order_id);
        Trades modify_order(Order modify_order);
    private:
        oms::ingredients::flat_map<common::Price, common::Size, std::less<>> bids_;
        oms::ingredients::flat_map<common::Price, common::Size, std::greater<>> asks_;

        std::unordered_map<uint64_t, Order> personal_orders_;
    };
}
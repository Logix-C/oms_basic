#pragma once

#include <ctime>
#include <unordered_map>
#include <ostream>

#include <order.hpp>
#include <trade.hpp>
#include <flat_map.hpp>
#include <spin_lock.hpp>

namespace test {
    class OrderbookTestFixture;
}

namespace oms {
    struct Orderbook {
        Orderbook(){};
        Orderbook(const Orderbook& other);
        Orderbook& operator=(const Orderbook& other);
        Orderbook(Orderbook&& other) noexcept;
        Orderbook& operator=(Orderbook&& other) noexcept;

        Trades add_order(Order order);
        void cancel_order(uint64_t order_id);
        Trades modify_order(const Order& modify_order);

        friend std::ostream& operator<<(std::ostream& os, const Orderbook& orderbook);
    private:
        oms::ingredients::flat_map<common::Price, common::Size, std::less<>> bids_;
        oms::ingredients::flat_map<common::Price, common::Size, std::greater<>> asks_;
        std::unordered_map<uint64_t, Order> personal_orders_;
        SpinLock spin_lock_;

        bool can_match(common::Side side, common::Price price);

        bool can_fully_fill(common::Side side, common::Price price, common::Size size);

        Trades match_orders(uint64_t order_id);

        void prune_day_orders();

        friend class test::OrderbookTestFixture;
    };
}

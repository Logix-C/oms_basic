#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <orderbook.hpp>
#include <order.hpp>
#include <common.hpp>

namespace test {
    class OrderbookTestFixture {
    public:
        const auto& bids(const oms::Orderbook& ob) { return ob.bids_; }
        const auto& asks(const oms::Orderbook& ob) { return ob.asks_; }
        const auto& personal_orders(const oms::Orderbook& ob) { return ob.personal_orders_; }

    protected:
        oms::Orderbook orderbook;
    };
}

TEST_CASE_METHOD(test::OrderbookTestFixture, "Add Buy Order", "[Orderbook]") {
    oms::common::Price price{static_cast<int64_t>(100.50)};
    oms::common::Size size{10};
    uint64_t order_id = 1;

    oms::Order buy_order(order_id, price, size, oms::common::Side::BID);
    auto trades = orderbook.add_order(buy_order);

    REQUIRE(trades.empty());
    REQUIRE(bids(orderbook).contains(price));
    REQUIRE(personal_orders(orderbook).contains(order_id));
}

TEST_CASE_METHOD(test::OrderbookTestFixture, "Add Sell Order", "[Orderbook]") {
    oms::common::Price price{static_cast<int64_t>(100.50)};
    oms::common::Size size{5};
    uint64_t order_id = 2;

    oms::Order sell_order(order_id, price, size, oms::common::Side::ASK);
    auto trades = orderbook.add_order(sell_order);

    REQUIRE(trades.empty());
    REQUIRE(asks(orderbook).contains(price));
    REQUIRE(personal_orders(orderbook).contains(order_id));
}

TEST_CASE_METHOD(test::OrderbookTestFixture, "Cancel Order", "[Orderbook]") {
    oms::common::Price price{static_cast<int64_t>(100.50)};
    oms::common::Size size{10};
    uint64_t order_id = 3;

    oms::Order buy_order(order_id, price, size, oms::common::Side::BID);
    orderbook.add_order(buy_order);
    orderbook.cancel_order(order_id);

    REQUIRE_FALSE(personal_orders(orderbook).contains(order_id));
    REQUIRE(bids(orderbook)[price].is_zero());
}

TEST_CASE_METHOD(test::OrderbookTestFixture, "Modify Order", "[Orderbook]") {
    oms::common::Price price{static_cast<int64_t>(100.50)};
    oms::common::Size size{10};
    uint64_t order_id = 4;

    oms::Order buy_order(order_id, price, size, oms::common::Side::BID);
    orderbook.add_order(buy_order);

    oms::common::Size new_size{15};
    oms::Order modified(order_id, price, new_size, oms::common::Side::BID);
    auto trades = orderbook.modify_order(modified);

    REQUIRE(trades.empty());
    REQUIRE(bids(orderbook)[price] == new_size);
}


TEST_CASE_METHOD(test::OrderbookTestFixture, "Match Orders", "[Orderbook]") {
    oms::common::Price bid_price{static_cast<int64_t>(101.00)};
    oms::common::Size bid_size{5};
    uint64_t bid_id = 5;

    oms::common::Price ask_price{static_cast<int64_t>(100.50)};
    oms::common::Size ask_size{5};
    uint64_t ask_id = 6;

    oms::Order buy_order(bid_id, bid_price, bid_size, oms::common::Side::BID);
    oms::Order sell_order(ask_id, ask_price, ask_size, oms::common::Side::ASK);

    orderbook.add_order(buy_order);
    auto trades = orderbook.add_order(sell_order);

    REQUIRE_FALSE(trades.empty());
    REQUIRE(bids(orderbook).empty());
    REQUIRE(asks(orderbook).empty());
}
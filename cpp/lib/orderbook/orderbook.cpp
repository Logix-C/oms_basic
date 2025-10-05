#include "orderbook.hpp"

namespace oms {
    Orderbook::Orderbook()
    : bids_(), asks_() {
    };

    Orderbook::Orderbook(const Orderbook& other) {

    };

    Orderbook& Orderbook::operator=(const Orderbook& other) {

    };

    Orderbook::Orderbook(Orderbook&& other) noexcept {

    };

    Orderbook& Orderbook::operator=(Orderbook&& other) noexcept {

    };

    Trades Orderbook::add_order(Order order) {

    }

    void Orderbook::cancel_order(uint64_t order_id) {

    }

    Trades Orderbook::modify_order(Order modify_order) {

    }
};
#include "orderbook.hpp"

namespace oms {
    Orderbook::Orderbook(){};

    Orderbook::Orderbook(const Orderbook& other)
        : bids_(other.bids_), asks_(other.asks_) {};

    Orderbook& Orderbook::operator=(const Orderbook& other) {
        if (this != &other) {
            bids_ = other.bids_;
            asks_ = other.asks_;
        }

        return *this;
    };

    Orderbook::Orderbook(Orderbook&& other) noexcept
        : bids_(std::move(other.bids_)), asks_(std::move(other.asks_)) {};

    Orderbook& Orderbook::operator=(Orderbook&& other) noexcept {
        if (this != &other) {
            bids_ = std::move(other.bids_);
            asks_ = std::move(other.asks_);
        }

        return *this;
    };

    Trades Orderbook::add_order(Order order) {
        if (personal_orders_.contains(order.id_)) {
            return {};
        }

        if (order.type_ == common::OrderType::MARKET) {
            if (order.side_ == common::Side::BID && !asks_.empty()) {
                // const auto& [worstAsk, _] = *asks_.begin();
                order.tif_ = common::OrderTIF::GTC;
            } else if (order.side_ == common::Side::ASK && !bids_.empty()) {
                // const auto& [worstBid, _] = *bids_.begin();
                order.tif_ = common::OrderTIF::GTC;
            } else {
                return { };
            }
        }

        if (order.tif_ == common::OrderTIF::FAK && !can_match(order.side_, order.price_)) {
            return {};
        }

        if (order.tif_ == common::OrderTIF::FOK && !can_fully_fill(order.side_, order.price_, order.size_)) {
            return {};
        }

        if (order.side_ == common::Side::BID) {
            bids_.insert({order.price_, order.size_});
        } else {
            asks_.insert({order.price_, order.size_});
        }

        personal_orders_[order.id_] = order;

        return match_orders(order.id_);
    }

    void Orderbook::cancel_order(uint64_t order_id) {
        if (!personal_orders_.contains(order_id)) {
            return;
        }

        const auto order = personal_orders_[order_id];
        personal_orders_.erase(order_id);

        if (order.side_ == common::Side::BID) {
            auto price = order.price_;
            bids_[price] -= order.size_;

            if (!bids_[price].is_zero()) {
                bids_.erase(price);
            }
        } else {
            auto price = order.price_;
            asks_[price] -= order.size_;

            if (!asks_[price].is_zero()) {
                asks_.erase(price);
            }
        }

    }

    Trades Orderbook::modify_order(const Order& modify_order) {
        if (!personal_orders_.contains(modify_order.id_)) {
            return {};
        }

        cancel_order(modify_order.id_);
        return add_order(modify_order);
    }

    bool Orderbook::can_match(common::Side side, common::Price price) {
        if (side == common::Side::BID) {
            if (asks_.empty()) {
                return false;
            }

            const auto& [best_ask, _] = *asks_.begin();
            return price >= best_ask;
        } else {
            if (bids_.empty()) {
                return false;
            }

            const auto& [best_bid, _] = *bids_.begin();
            return price <= best_bid;
        }
    };

    bool Orderbook::can_fully_fill(common::Side side, common::Price price, common::Size size) {
        if (!can_match(side, price))
            return false;

        common::Size accumulated{0};
        if (side == common::Side::BID) {
            for (const auto& [levelPrice, levelSize] : asks_) {
                if (levelPrice > price) {
                    break;
                }

                accumulated += levelSize;
                if (accumulated >= size)
                    return true;
            }
        } else {
            for (const auto& [levelPrice, levelSize] : bids_) {
                if (levelPrice < price) {
                    break;
                }

                accumulated += levelSize;
                if (accumulated >= size)
                    return true;
            }
        }

        return false;
    };

    Trades Orderbook::match_orders(uint64_t order_id) {
        Trades trades;

        while (bids_.empty() || asks_.empty()) {
            auto& [bid_price, bid_size] = *bids_.begin();
            auto& [ask_price, ask_size] = *asks_.begin();

            if (bid_price < ask_price)
                break;

            common::Size filled_size = std::min(bid_size, ask_size);

            trades.push_back(Trade{
                .id_ = 1,
                .price_ = bid_price,
                .size_ = bid_size,
                .side_ = common::Side::BID
            });

            bid_size -= filled_size;
            ask_size -= filled_size;

            if (bids_[bid_price].is_zero()) {
                bids_.erase(bid_price);
            }

            if (asks_[ask_price].is_zero()) {
                asks_.erase(ask_price);
            }
        }

        if (!bids_.empty()) {
            // const auto& [price, size] = *bids_.rbegin();
            if (personal_orders_[order_id].tif_ == common::OrderTIF::FAK) {
                cancel_order(order_id);
            }
        }

        if (!asks_.empty()) {
            // const auto& [price, size] = *asks_.rbegin();
            if (personal_orders_[order_id].tif_ == common::OrderTIF::FAK) {
                cancel_order(order_id);
            }
        }

        return trades;
    };
};
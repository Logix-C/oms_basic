#pragma once

#include <ostream>
#include <string>

namespace oms::utils {
    template <int Scale, int64_t TickSize = 1>
    struct Decimal {
        static constexpr int Scale_ = Scale;
        static constexpr int TickSize_ = TickSize;

        constexpr Decimal() : decimal_(0) {}

        explicit constexpr Decimal(int64_t decimal) : decimal_(decimal) {}

        static constexpr Decimal from_double(double val){
            if constexpr (Scale > 0) {
                return Decimal(static_cast<int64_t>(val >= 0.0
                                                        ? val * Scale + 0.5
                                                        : val * Scale - 0.5));
            } else {
                return Decimal(0);
            }
        }

        static constexpr Decimal from_raw(int64_t decimal) { return Decimal(decimal); }

        [[nodiscard]] constexpr double to_double() const { return static_cast<double>(decimal_) / Scale; }

        [[nodiscard]] constexpr int64_t raw() const { return decimal_; }

        constexpr Decimal round_tick() const { return Decimal((decimal_ / TickSize) * TickSize); }

        constexpr auto operator<=>(const Decimal&) const = default;
        constexpr bool operator==(const Decimal&) const = default;

        constexpr bool operator<(const Decimal& other) const { return decimal_ < other.decimal_; }
        constexpr bool operator>(const Decimal& other) const { return decimal_ > other.decimal_; }
        constexpr bool operator<=(const Decimal& other) const { return decimal_ <= other.decimal_; }
        constexpr bool operator>=(const Decimal& other) const { return decimal_ >= other.decimal_; }

        constexpr friend Decimal operator*(int64_t x, Decimal d) { return Decimal(x * d.decimal_); }

        constexpr Decimal& operator+=(const Decimal& other){
            decimal_ += other.decimal_;
            return *this;
        }

        constexpr Decimal& operator-=(const Decimal& other){
            decimal_ -= other.decimal_;
            return *this;
        }

        constexpr Decimal& operator*=(const Decimal& other){
            *this = *this * other;
            return *this;
        }

        constexpr Decimal& operator/=(const Decimal& other){
            *this = *this / other;
            return *this;
        }

        [[nodiscard]] constexpr bool is_zero() const { return decimal_ == 0; }

        [[nodiscard]] std::string to_string() const{
            return std::to_string(to_double());
        }

    private:
        int64_t decimal_;
    };

    template <int Scale_, int64_t TickSize_>
    std::ostream& operator<<(std::ostream& os, const Decimal<Scale_, TickSize_>& value){
        return os << value.to_double();
    }
}
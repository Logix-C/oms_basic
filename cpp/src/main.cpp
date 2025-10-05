#include <iostream>
#include <type_traits>

#include <orderbook.hpp>
#include <order.hpp>

int main() {
    std::cout << std::is_pod<oms::Order>::value << std::endl;
    std::cout << std::is_trivially_copyable<oms::Order>::value << std::endl;
    oms::Orderbook orderbook{};
}

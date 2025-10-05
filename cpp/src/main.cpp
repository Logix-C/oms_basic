#include <iostream>

#include <orderbook.hpp>
#include <order.hpp>
#include <type_traits>

int main() {
    std::cout << std::is_pod<oms::Order>::value << std::endl;
    std::cout << std::is_trivially_copyable<oms::Order>::value << std::endl;
    oms::Orderbook orderbook{};
}

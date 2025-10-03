add_library(
        core.lib
        STATIC
        lib/common/order_type.cpp
        lib/common/side.cpp
        lib/order/order.cpp
        lib/trade/trade.cpp
        lib/orderbook/orderbook.cpp
)

target_include_directories(
        core.lib
        PUBLIC
        lib/common
        lib/order
        lib/trade
        lib/orderbook
)

add_executable(
        oms.bin
        src/main.cpp
)

target_include_directories(
        oms.bin
        PRIVATE
        core.lib
)
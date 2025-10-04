add_library(
        core.lib
        STATIC
        lib/util/base/decimal.cpp
        lib/ingredients/flat_map/flat_map.cpp
        lib/common/common.cpp

        lib/order/order.cpp
        lib/trade/trade.cpp
        lib/orderbook/orderbook.cpp
)

target_include_directories(
        core.lib
        PUBLIC
        lib/util/base
        lib/ingredients/flat_map
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
add_library(
        core_lib
        STATIC
        lib/util/base/decimal.cpp
        lib/util/spin_lock/spin_lock.cpp
        lib/ingredients/flat_map/flat_map.cpp
        lib/common/common.cpp

        lib/order/order.cpp
        lib/trade/trade.cpp
        lib/orderbook/orderbook.cpp
)

target_include_directories(
        core_lib
        PUBLIC
        lib/util/base
        lib/util/spin_lock
        lib/ingredients/flat_map
        lib/common
        lib/order
        lib/trade
        lib/orderbook
)

add_executable(
        oms_bin
        src/main.cpp
)

target_include_directories(
        oms_bin
        PRIVATE
        core_lib
        lib/util/base
        lib/common
        lib/ingredients/flat_map
        lib/order
        lib/trade
        lib/orderbook
)

target_link_libraries(oms_bin PRIVATE core_lib)

add_executable(
        oms_bin_test
        tests/test_orderbook.cpp
)

target_link_libraries(
        oms_bin_test
        PRIVATE
        Catch2::Catch2WithMain
        core_lib
)

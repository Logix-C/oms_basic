#pragma once

enum class OrderType {
    LIMIT = 0,
    MARKET = 1
};

enum class OrderTIF {
    GTC = 0,
    FAK = 1,
    FOK = 2,
    DAY = 3
};
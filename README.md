**<h1>Order Management System</h1>**

![hippo](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExd3ZmaXRnenZ3aDJidXQ4aWhkM3NicnJoa3RpOGRsNjJleGxmdzI2OCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/KEYEpIngcmXlHetDqz/giphy.gif)

<h2>Static Lib & Public API</h2>
```c++
#include <orderbook.hpp>

Trades add_order(Order order);

void cancel_order(uint64_t order_id);

Trades modify_order(const Order& modify_order);
```
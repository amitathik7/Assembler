#ifndef ORDER_STRUCT_H
#define ORDER_STRUCT_H

#include <cstdint>

constexpr unsigned PRICE_SCALAR = 10;
constexpr unsigned QUANTITY_SCALAR = 1000;

using ScalarPriceType = std::uint32_t;
using ScalarQuantityType = std::uint32_t;
using OrderIdType = std::uint64_t;

enum class Side : std::uint8_t {
    Buy = 0,
    Sell = 1
};

struct Order {
    OrderIdType order_id;
    ScalarPriceType price;    // Decimal Price x PRICE_SCALAR
    ScalarQuantityType quantity; // Decimal Quantity x QUANTITY_SCALAR
    Side side;
    Order *previous_order = nullptr;
    Order *next_order = nullptr;
};

#endif

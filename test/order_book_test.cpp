#include <assembler/order_book.hpp>
#include <assembler/order_struct.hpp>
#include <gtest/gtest.h>

TEST(OrderBookTest, Smoke) { EXPECT_EQ(placeholder(), 42); }

TEST(OrderStructTest, PreviousPointerIsNullptr) {
    Order new_order = Order();

    EXPECT_EQ(new_order.previous_order, nullptr);
}

TEST(OrderStructTest, NextPointerIsNullptr) {
    Order new_order = Order();

    EXPECT_EQ(new_order.next_order, nullptr);
}

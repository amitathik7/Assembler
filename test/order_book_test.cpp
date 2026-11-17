#include <assembler/order_book.hpp>
#include <assembler/order_struct.hpp>
#include <assembler/price_level_struct.hpp>
#include <gtest/gtest.h>

TEST(OrderStructTest, PreviousPointerIsNullptr) {
    Order new_order = Order();

    EXPECT_EQ(new_order.previous_order, nullptr);
}

TEST(OrderStructTest, NextPointerIsNullptr) {
    Order new_order = Order();

    EXPECT_EQ(new_order.next_order, nullptr);
}

TEST(PriceLevelStructTest, RejectsOpposingSide1) {
    Order new_order = Order();
    new_order.side = Side::Buy;

    PriceLevel new_price_level = PriceLevel();
    new_price_level.side = Side::Sell;

    EXPECT_EQ(new_price_level.add_order(&new_order), false);
}

TEST(PriceLevelStructTest, RejectsOpposingSide2) {
    Order new_order = Order();
    new_order.side = Side::Sell;

    PriceLevel new_price_level = PriceLevel();
    new_price_level.side = Side::Buy;

    EXPECT_EQ(new_price_level.add_order(&new_order), false);
}

TEST(PriceLevelStructTest, AcceptsSameSide1) {
    Order new_order = Order();
    new_order.side = Side::Buy;

    PriceLevel new_price_level = PriceLevel();
    new_price_level.side = Side::Buy;

    EXPECT_EQ(new_price_level.add_order(&new_order), true);
}

TEST(PriceLevelStructTest, AcceptsSameSide2) {
    Order new_order = Order();
    new_order.side = Side::Sell;

    PriceLevel new_price_level = PriceLevel();
    new_price_level.side = Side::Sell;

    EXPECT_EQ(new_price_level.add_order(&new_order), true);
}

TEST(PriceLevelStructTest, AddToEmptyLevelSetsHeadTailAndQuantity) {
    Order order = Order();
    order.side = Side::Buy;
    order.quantity = 5;

    PriceLevel level = PriceLevel();
    level.side = Side::Buy;

    ASSERT_TRUE(level.add_order(&order));

    EXPECT_EQ(level.head_order, &order);
    EXPECT_EQ(level.tail_order, &order);
    EXPECT_EQ(level.quantity, 5u);
    EXPECT_EQ(order.previous_order, nullptr);
    EXPECT_EQ(order.next_order, nullptr);
}

TEST(PriceLevelStructTest, AddToNonEmptyLevelLinksOrdersInArrivalOrder) {
    Order a = Order();
    a.side = Side::Sell;
    a.quantity = 5;
    Order b = Order();
    b.side = Side::Sell;
    b.quantity = 3;
    Order c = Order();
    c.side = Side::Sell;
    c.quantity = 7;

    PriceLevel level = PriceLevel();
    level.side = Side::Sell;

    ASSERT_TRUE(level.add_order(&a));
    ASSERT_TRUE(level.add_order(&b));
    ASSERT_TRUE(level.add_order(&c));

    // head -> a -> b -> c <- tail
    EXPECT_EQ(level.head_order, &a);
    EXPECT_EQ(level.tail_order, &c);

    EXPECT_EQ(a.previous_order, nullptr);
    EXPECT_EQ(a.next_order, &b);
    EXPECT_EQ(b.previous_order, &a);
    EXPECT_EQ(b.next_order, &c);
    EXPECT_EQ(c.previous_order, &b);
    EXPECT_EQ(c.next_order, nullptr);

    // Different quantities so that overwriting (=) instead of summing (+=) is caught.
    EXPECT_EQ(level.quantity, 15u);
}

TEST(PriceLevelStructTest, RejectedOrderLeavesLevelUnchanged) {
    Order existing = Order();
    existing.side = Side::Buy;
    existing.quantity = 4;
    Order wrong_side = Order();
    wrong_side.side = Side::Sell;
    wrong_side.quantity = 9;

    PriceLevel level = PriceLevel();
    level.side = Side::Buy;
    ASSERT_TRUE(level.add_order(&existing));

    EXPECT_FALSE(level.add_order(&wrong_side));

    EXPECT_EQ(level.head_order, &existing);
    EXPECT_EQ(level.tail_order, &existing);
    EXPECT_EQ(level.quantity, 4u);
    EXPECT_EQ(existing.next_order, nullptr);
    EXPECT_EQ(wrong_side.previous_order, nullptr);
    EXPECT_EQ(wrong_side.next_order, nullptr);
}

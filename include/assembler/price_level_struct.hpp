#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

#include <assembler/order_struct.hpp>

struct PriceLevel {
    ScalarQuantityType quantity = 0;
    ScalarPriceType price = 0;
    Side side;

    // Stores the oldest order (i.e. the next order to be fulfilled at this price level).
    Order *head_order = nullptr;
    // Stores the newest order.
    Order *tail_order = nullptr;

    // If Buy then the next lowest price level with availability. Else (Sell) it's the next highest
    // price level with availability.
    PriceLevel *next_level = nullptr;
    // Reverse of next_level.
    PriceLevel *previous_level = nullptr;

    bool add_order(Order *o) {
        if (this->side != o->side) {
            return false;
        }

        if (this->head_order == nullptr) {
            this->head_order = o;
            this->tail_order = o;
        } else {
            o->previous_order = this->tail_order;
            this->tail_order = o;
            o->previous_order->next_order = o;
        }

        this->quantity += o->quantity;
        return true;
    }
};

#endif

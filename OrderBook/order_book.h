#pragma once

#include "../hashing/open_address_hash.h"
#include "../list/linked_list.h"
#include "order.h"
#include "pool.h"
#include "price_level.h"

template <typename PriceIndexType> class OrderBook {
private:
  PriceIndexType bids_;
  PriceIndexType asks_;
  Pool<Order> order_pool_;
  OpenAddressHash<OrderId, Order*> orders_;
  LinkedList<Trade> trades_;

  PriceIndexType& side_index(Side side) {
    return side == Side::kBuy ? bids_ : asks_;
  }

  Quantity match(Side taker_side, Price limit_price, Quantity quantity,
                 OrderId taker_id, bool is_market) {
    PriceIndexType& opposite = taker_side == Side::kBuy ? asks_ : bids_;
    while (quantity > 0) {
      PriceLevel* level = opposite.best();
      if (!level) {
        break;
      }
      if (!is_market && (taker_side == Side::kBuy
                             ? level->price > limit_price
                             : level->price < limit_price)) {
        break;
      }
      while (quantity > 0 && !level->orders.empty()) {
        Order* maker = level->orders.front();
        Quantity fill =
            maker->quantity < quantity ? maker->quantity : quantity;
        maker->quantity -= fill;
        level->total_quantity -= fill;
        quantity -= fill;
        trades_.push_back(Trade{maker->id, taker_id, level->price, fill});
        if (maker->quantity == 0) {
          level->orders.erase(maker);
          orders_.remove(maker->id);
          order_pool_.deallocate(maker);
        }
      }
      if (level->orders.empty()) {
        opposite.remove(level->price);
      }
    }
    return quantity;
  }

public:
  template <typename... Args>
  explicit OrderBook(Args... args)
      : bids_(Side::kBuy, args...), asks_(Side::kSell, args...) {}

  bool add_limit_order(OrderId id, Side side, Price price, Quantity quantity) {
    if (quantity <= 0 || orders_.contains(id)) {
      return false;
    }
    Quantity remaining = match(side, price, quantity, id, false);
    if (remaining == 0) {
      return true;
    }
    PriceLevel* level = side_index(side).find_or_create(price);
    Order* order = order_pool_.allocate();
    order->id = id;
    order->side = side;
    order->price = price;
    order->quantity = remaining;
    level->orders.push_back(order);
    level->total_quantity += remaining;
    orders_.insert(id, order);
    return true;
  }

  Quantity add_market_order(OrderId id, Side side, Quantity quantity) {
    if (quantity <= 0) {
      return 0;
    }
    return quantity - match(side, 0, quantity, id, true);
  }

  bool cancel(OrderId id) {
    if (!orders_.contains(id)) {
      return false;
    }
    Order* order = orders_.get(id);
    PriceIndexType& index = side_index(order->side);
    PriceLevel* level = index.find(order->price);
    level->orders.erase(order);
    level->total_quantity -= order->quantity;
    if (level->orders.empty()) {
      index.remove(order->price);
    }
    orders_.remove(id);
    order_pool_.deallocate(order);
    return true;
  }

  bool best_bid(Price* best_price) {
    PriceLevel* level = bids_.best();
    if (!level) {
      return false;
    }
    *best_price = level->price;
    return true;
  }

  bool best_ask(Price* best_price) {
    PriceLevel* level = asks_.best();
    if (!level) {
      return false;
    }
    *best_price = level->price;
    return true;
  }

  Quantity bid_quantity_at(Price price) {
    PriceLevel* level = bids_.find(price);
    return level ? level->total_quantity : 0;
  }

  Quantity ask_quantity_at(Price price) {
    PriceLevel* level = asks_.find(price);
    return level ? level->total_quantity : 0;
  }

  size_t open_orders() const { return orders_.size(); }

  const LinkedList<Trade>& trades() const { return trades_; }
};

#pragma once

#include "../list/vector.h"
#include "order.h"
#include "pool.h"
#include "price_level.h"
#include <cassert>

class LadderPriceIndex {
private:
  Vector<PriceLevel*> slots_;
  Pool<PriceLevel> pool_;
  Price min_price_;
  Price max_price_;
  Price best_;
  size_t num_levels_;
  bool is_bid_;

  size_t index_of(Price price) const {
    return static_cast<size_t>(price - min_price_);
  }

public:
  LadderPriceIndex(Side side, Price min_price, Price max_price)
      : slots_(static_cast<size_t>(max_price - min_price + 1)),
        min_price_(min_price), max_price_(max_price), best_(0), num_levels_(0),
        is_bid_(side == Side::kBuy) {
    assert(max_price >= min_price);
  }

  PriceLevel* find(Price price) {
    if (price < min_price_ || price > max_price_) {
      return nullptr;
    }
    return slots_[index_of(price)];
  }

  PriceLevel* find_or_create(Price price) {
    assert(price >= min_price_ && price <= max_price_);
    size_t index = index_of(price);
    if (slots_[index]) {
      return slots_[index];
    }
    PriceLevel* level = pool_.allocate();
    level->price = price;
    level->total_quantity = 0;
    slots_[index] = level;
    ++num_levels_;
    if (num_levels_ == 1 || (is_bid_ ? price > best_ : price < best_)) {
      best_ = price;
    }
    return level;
  }

  void remove(Price price) {
    if (price < min_price_ || price > max_price_) {
      return;
    }
    size_t index = index_of(price);
    if (!slots_[index]) {
      return;
    }
    pool_.deallocate(slots_[index]);
    slots_[index] = nullptr;
    --num_levels_;
    if (num_levels_ == 0 || price != best_) {
      return;
    }
    Price probe = price;
    if (is_bid_) {
      while (!slots_[index_of(probe)]) {
        --probe;
      }
    } else {
      while (!slots_[index_of(probe)]) {
        ++probe;
      }
    }
    best_ = probe;
  }

  PriceLevel* best() {
    return num_levels_ ? slots_[index_of(best_)] : nullptr;
  }

  bool empty() const { return num_levels_ == 0; }
};

#pragma once

#include "../tree/red_black_tree.h"
#include "order.h"
#include "pool.h"
#include "price_level.h"

class TreePriceIndex {
private:
  struct LevelEntry {
    Price price;
    PriceLevel* level;

    bool operator<(const LevelEntry& other) const {
      return price < other.price;
    }
  };

  RedBlackTree<LevelEntry> levels_;
  Pool<PriceLevel> pool_;
  bool is_bid_;

public:
  explicit TreePriceIndex(Side side) : is_bid_(side == Side::kBuy) {}

  PriceLevel* find(Price price) {
    LevelEntry* entry = levels_.find(LevelEntry{price, nullptr});
    return entry ? entry->level : nullptr;
  }

  PriceLevel* find_or_create(Price price) {
    if (PriceLevel* existing = find(price)) {
      return existing;
    }
    PriceLevel* level = pool_.allocate();
    level->price = price;
    level->total_quantity = 0;
    levels_.insert(LevelEntry{price, level});
    return level;
  }

  void remove(Price price) {
    LevelEntry probe{price, nullptr};
    LevelEntry* entry = levels_.find(probe);
    if (!entry) {
      return;
    }
    pool_.deallocate(entry->level);
    levels_.remove(probe);
  }

  PriceLevel* best() {
    if (levels_.empty()) {
      return nullptr;
    }
    return is_bid_ ? levels_.max().level : levels_.min().level;
  }

  bool empty() const { return levels_.empty(); }
};

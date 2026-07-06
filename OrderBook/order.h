#pragma once

#include <cstdint>

using Price = int64_t;
using Quantity = int64_t;
using OrderId = uint64_t;

enum class Side { kBuy, kSell };

struct Order {
  OrderId id = 0;
  Side side = Side::kBuy;
  Price price = 0;
  Quantity quantity = 0;
  Order* prev = nullptr;
  Order* next = nullptr;
};

struct Trade {
  OrderId maker_id = 0;
  OrderId taker_id = 0;
  Price price = 0;
  Quantity quantity = 0;
};

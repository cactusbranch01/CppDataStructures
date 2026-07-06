#pragma once

#include "../list/intrusive_list.h"
#include "order.h"

struct PriceLevel {
  Price price = 0;
  Quantity total_quantity = 0;
  IntrusiveList<Order> orders;
};

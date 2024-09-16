#include "childseat.h"

#include "message.h"

ChildSeat::ChildSeat(const std::string &reference, int days)
    : AddOn(reference, days, Message::ADDON_CHILD_SEAT_NAME.GetMessage()) {
  reference_ = reference;
  days_ = days;
  cost_ = CalculateCost();
}

int ChildSeat::CalculateCost() const {
  int cost = 2 * days_;
  if (cost > 10) {
    return 10;
  } else {
    return cost;
  }
}

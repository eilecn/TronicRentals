#include "gps.h"

#include <string>

#include "message.h"

Gps::Gps(const std::string &reference, int days)
    : AddOn(reference, days, Message::ADDON_GPS_UNIT_NAME.GetMessage()) {
  reference_ = reference;
  days_ = days;
  cost_ = CalculateCost();
}

int Gps::CalculateCost() const {
  int cost = 5 * days_;
  if (cost > 25) {
    return 25;
  } else {
    return cost;
  }
}

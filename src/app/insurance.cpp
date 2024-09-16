#include "insurance.h"

#include <iostream>

#include "car.h"
#include "message.h"
using namespace std;

Insurance::Insurance(const std::string &reference, int days,
                     int total_rental_fee)
    : AddOn(reference, days, Message::ADDON_INSURANCE_NAME.GetMessage()) {
  reference_ = reference;
  days_ = days;
  total_rental_fee_ = total_rental_fee;
  cost_ = CalculateCost();
}

int Insurance::CalculateCost() const {
  int cost = (total_rental_fee_ * 5) / 100;
  return cost;
}

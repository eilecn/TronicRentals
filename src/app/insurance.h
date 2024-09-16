#ifndef INSURANCE_H
#define INSURANCE_H
#include "addon.h"

class Insurance : public AddOn {
 public:
  Insurance(const std::string &reference, int days, int total_rental_fee);
  int CalculateCost() const override;

 private:
  int total_rental_fee_;
};

#endif

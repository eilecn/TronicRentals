#ifndef CHILDSEAT_H
#define CHILDSEAT_H
#include <string>

#include "addon.h"

class ChildSeat : public AddOn {
 public:
  ChildSeat(const std::string &reference, int days);
  int CalculateCost() const override;

 private:
};

#endif

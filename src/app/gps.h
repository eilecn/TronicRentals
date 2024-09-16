#ifndef GPS_H
#define GPS_H
#include "addon.h"

class Gps : public AddOn {
 public:
  Gps(const std::string &reference, int days);
  int CalculateCost() const override;

 private:
};

#endif

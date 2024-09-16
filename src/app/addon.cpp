#include "addon.h"

#include <string>

AddOn::AddOn(const std::string reference, int days, std::string add_on_type) {
  reference_ = reference;
  days_ = days;
  add_on_type_ = add_on_type;
}

int AddOn::GetDays() const { return days_; }

std::string AddOn::GetReference() const { return reference_; }

int AddOn::GetCost() const { return cost_; }

int AddOn::CalculateCost() const { return 0; }

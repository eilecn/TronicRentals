#ifndef ADDON_H
#define ADDON_H
#include <string>

class AddOn {
 public:
  AddOn(const std::string reference, int days, std::string add_on_type);
  virtual int CalculateCost() const = 0;
  int GetDays() const;
  std::string GetReference() const;
  int GetCost() const;

 protected:
  int cost_;
  int days_;
  std::string reference_;
  std::string add_on_type_;
};

#endif

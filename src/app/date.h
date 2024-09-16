#ifndef DATE_H
#define DATE_H
#include <string>

class Date {
 public:
  Date(const std::string &date);
  bool operator>(const Date &other) const;
  bool operator>=(const Date &other) const;
  int GetDay() const;
  int GetMonth() const;
  int GetYear() const;
  std::string GetDate() const;

 private:
  std::string date_;
  int date_day_;
  int date_month_;
  int date_year_;
};

#endif

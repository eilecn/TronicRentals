#include <iostream>
using namespace std;
#include <string>

#include "date.h"

Date::Date(const std::string &date) {
  date_ = date;
  date_day_ = stoi(date_.substr(0, 2));
  date_month_ = stoi(date_.substr(3, 2));
  date_year_ = stoi(date_.substr(6, 4));
}

bool Date::operator>(const Date &other) const {
  if (date_year_ > other.date_year_) {
    return 1;
  } else if (date_month_ > other.date_month_ &&
             date_year_ == other.date_year_) {
    return 1;
  } else if (date_day_ > other.date_day_ && date_month_ == other.date_month_ &&
             date_year_ == other.date_year_) {
    return 1;
  }
  return 0;
}

bool Date::operator>=(const Date &other) const {
  if (date_year_ > other.date_year_) {
    return 1;
  } else if (date_month_ > other.date_month_ &&
             date_year_ == other.date_year_) {
    return 1;
  } else if (date_day_ >= other.date_day_ && date_month_ == other.date_month_ &&
             date_year_ == other.date_year_) {
    return 1;
  }
  return 0;
}

int Date::GetDay() const { return date_day_; }

int Date::GetMonth() const { return date_month_; }

int Date::GetYear() const { return date_year_; }

string Date::GetDate() const { return date_; }

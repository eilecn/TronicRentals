#include "rental.h"

#include <iostream>
using namespace std;
#include <string>

Rental::Rental(const std::string& registration, const std::string& start_date,
               const std::string& end_date, const std::string& user_id,
               const std::string& reference) {
  rental_registration_ = registration;
  rental_start_ = start_date;
  rental_end_ = end_date;
  rental_id_ = user_id;
  rental_reference_ = reference;
  gps_ = 0;
  child_seat_ = 0;
  insurance_ = 0;
}

string Rental::GetRentalStartDate() const { return rental_start_; }

string Rental::GetRentalEndDate() const { return rental_end_; }

string Rental::GetRentalRegistration() const { return rental_registration_; }

string Rental::GetRentalReference() const { return rental_reference_; }

string Rental::GetRentalId() const { return rental_id_; }

void Rental::AddGpsUnit() { gps_ = 1; }

void Rental::AddChildSeat() { child_seat_ = 1; }

void Rental::AddInsurance() { insurance_ = 1; }

bool Rental::GetGps() const {
  if (gps_ == 1) {
    return 1;
  } else {
    return 0;
  }
}

bool Rental::GetChildSeat() const {
  if (child_seat_ == 1) {
    return 1;
  } else {
    return 0;
  }
}

bool Rental::GetInsurance() const {
  if (insurance_ == 1) {
    return 1;
  } else {
    return 0;
  }
}

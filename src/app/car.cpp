#include "car.h"

#include <iostream>
using namespace std;
#include <string>

#include "message.h"

Car::Car(const std::string& registration_plate, const std::string& make,
         const std::string& daily_rental_fee) {
  registration_plate_ = registration_plate;
  make_ = make;
  daily_rental_fee_ = daily_rental_fee;
  availability_ = 1;
}

void Car::DisplayCarInfo() const {
  if (availability_ == 1) {
    Message::LIST_CAR_ENTRY.PrintMessage(
        {registration_plate_, make_, daily_rental_fee_, ""});
  } else {
    Message::LIST_CAR_ENTRY.PrintMessage(
        {registration_plate_, make_, daily_rental_fee_, " not"});
  }
}

string Car::GetRegistrationPlate() const { return registration_plate_; }

bool Car::CheckValidPlate() {
  for (int i = 0; i < registration_plate_.length(); i++) {
    registration_plate_[i] = toupper(registration_plate_[i]);
  }
  if (registration_plate_.length() != 6) {
    return 0;
  }
  for (int i = 0; i < 3; i++) {
    if (isalpha(registration_plate_[i]) == 0) {
      return 0;
    }
  }
  for (int i = 3; i < 6; i++) {
    if (isdigit(registration_plate_[i]) == 0) {
      return 0;
    }
  }
  return 1;
}

void Car::PrintMakeFormat() {
  for (int i = 0; i < make_.length(); i++) {
    if (i == 0) {
      make_[i] = toupper(make_[i]);
    } else {
      make_[i] = tolower(make_[i]);
    }
  }
}

bool Car::CheckValidFee() {
  if (daily_rental_fee_[0] == '-' ||
      (daily_rental_fee_.length() == 1 && daily_rental_fee_[0] == '0')) {
    Message::RENTAL_FEE_NOT_POSITIVE.PrintMessage();
    return 0;
  }
  for (int i = 0; i < daily_rental_fee_.length(); i++) {
    if (isdigit(daily_rental_fee_[i]) == 0) {
      Message::RENTAL_FEE_MUST_BE_NUMERIC.PrintMessage();
      return 0;
    }
  }
  return 1;
}

bool Car::GetAvailability() const {
  if (availability_ == 1) {
    return 1;
  } else {
    return 0;
  }
}

void Car::MakeCarAvailable() { availability_ = 1; }

void Car::MakeCarNotAvailable() { availability_ = 0; }

int Car::GetDailyRentalFee() const { return stoi(daily_rental_fee_); }

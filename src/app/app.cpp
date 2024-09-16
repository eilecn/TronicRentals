#include "app.h"

#include <iostream>
#include <string>
#include <vector>

#include "addon.h"
#include "car.h"
#include "childseat.h"
#include "date.h"
#include "gps.h"
#include "insurance.h"
#include "message.h"
#include "rental.h"
#include "utils.h"

using namespace std;

/*
----------------------------------------------------------------------------
  This is where you start.
  However, make sure you do not not write all your code in a single file!
----------------------------------------------------------------------------
*/

App::App() {}

void App::CreateCar(const std::string &registration_plate,
                    const std::string &make,
                    const std::string &daily_rental_fee) {
  Car new_car(registration_plate, make, daily_rental_fee);
  new_car.PrintMakeFormat();
  if (new_car.CheckValidPlate() == 0) {
    Message::INVALID_REGISTRATION_PLATE.PrintMessage(
        {new_car.GetRegistrationPlate()});
    return;
  }
  for (int i = 0; i < car_list_.size(); i++) {
    if (new_car.GetRegistrationPlate() == car_list_[i].GetRegistrationPlate()) {
      Message::CAR_ALREADY_EXISTS.PrintMessage(
          {new_car.GetRegistrationPlate()});
      return;
    }
  }
  if (new_car.CheckValidFee() == 0) {
    return;
  }
  Message::CAR_CREATED.PrintMessage({new_car.GetRegistrationPlate()});
  car_list_.push_back(new_car);
}

void App::DisplayCars() const {
  int car_list_length = car_list_.size();
  if (car_list_length == 0) {
    Message::NO_CARS_AVAILABLE.PrintMessage();
  } else if (car_list_length == 1) {
    string is_or_are = "is";
    string number_of_cars = "1";
    string plural_or_not = "";
    Message::NUMBER_OF_CARS_AVAILABLE.PrintMessage(
        {is_or_are, number_of_cars, plural_or_not});
    for (int i = 0; i < car_list_length; i++) {
      car_list_[i].DisplayCarInfo();
    }
  } else if (car_list_length > 1) {
    string is_or_are = "are";
    string number_of_cars = to_string(car_list_length);
    string plural_or_not = "s";
    Message::NUMBER_OF_CARS_AVAILABLE.PrintMessage(
        {is_or_are, number_of_cars, plural_or_not});
    for (int i = 0; i < car_list_length; i++) {
      car_list_[i].DisplayCarInfo();
    }
  }
}

void App::ConfigureDate(const std::string &date) {
  day2_ = stoi(date.substr(0, 2));
  month2_ = stoi(date.substr(3, 2));
  year2_ = stoi(date.substr(6, 4));
  Date new_date(date);
  if (configured_date_.length() == 0) {
    configured_date_ = date;
    day1_ = stoi(date.substr(0, 2));
    month1_ = stoi(date.substr(3, 2));
    year1_ = stoi(date.substr(6, 4));
    Message::DATE_CONFIGURED.PrintMessage({configured_date_});
  } else if (CheckValidStartDate(date) == 1) {
    configured_date_ = date;
    day1_ = stoi(date.substr(0, 2));
    month1_ = stoi(date.substr(3, 2));
    year1_ = stoi(date.substr(6, 4));
    Message::DATE_CONFIGURED.PrintMessage({configured_date_});
  } else {
    Message::DATE_BEFORE_CURRENT.PrintMessage();
  }

  for (int i = 0; i < car_list_.size(); i++) {
    for (int j = 0; j < rental_list_.size(); j++) {
      if (car_list_[i].GetRegistrationPlate() ==
          rental_list_[j].GetRentalRegistration()) {
        if (CheckCarAvailability(configured_date_,
                                 rental_list_[j].GetRentalStartDate(),
                                 rental_list_[j].GetRentalEndDate()) == 1) {
          car_list_[i].MakeCarAvailable();
        } else {
          car_list_[i].MakeCarNotAvailable();
        }
      }
    }
  }
}

bool App::CheckCarAvailability(const std::string &system_date,
                               const std::string start_date,
                               const std::string end_date) const {
  std::vector<string> date_range_list;
  int duration = CalculateRentalDuration(start_date, end_date);
  for (int i = 0; i < duration; i++) {
    std::string date_to_push =
        to_string(stoi(start_date.substr(0, 2)) + i) + start_date.substr(2, 8);
    date_range_list.push_back(date_to_push);
  }
  for (int i = 0; i < date_range_list.size(); i++) {
    if (date_range_list[i] == system_date) {
      return 0;
    }
  }
  return 1;
}

void App::DisplayDate() const {
  if (configured_date_.length() == 0) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
  } else {
    Message::DATE_CURRENTLY.PrintMessage({configured_date_});
  }
}

void App::CreateRental(const std::vector<std::string> options) {
  if (configured_date_.length() == 0) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
    return;
  }
  registration_ = options[0];
  Date start_date_(options[1]);
  Date end_date_(options[2]);
  user_id_ = options[3];

  for (int i = 0; i < registration_.length(); i++) {
    registration_[i] = toupper(registration_[i]);
  }
  for (int i = 0; i < user_id_.length(); i++) {
    user_id_[i] = tolower(user_id_[i]);
  }
  if (CheckForRegistration(registration_) != 1) {
    Message::NO_CAR_WITH_PLATE.PrintMessage({registration_});
    return;
  }
  if (CheckValidStartDate(start_date_) == 1) {
    start_day_ = stoi(start_date_.GetDate().substr(0, 2));
    start_month_ = stoi(start_date_.GetDate().substr(3, 2));
    start_year_ = stoi(start_date_.GetDate().substr(6, 4));
  } else {
    Message::START_DATE_BEFORE_TODAY.PrintMessage({configured_date_});
    return;
  }

  if (CheckValidEndDate(end_date_) != 1) {
    Message::END_DATE_BEFORE_START.PrintMessage({start_date_.GetDate()});
    return;
  }

  if (CheckForRegistration(registration_) == 1 &&
      CheckValidStartDate(start_date_) == 1 &&
      CheckValidEndDate(end_date_) == 1) {
    int reference_number = 1;
    for (int i = 0; i < rental_list_.size(); i++) {
      if (rental_list_[i].GetRentalRegistration() == registration_) {
        reference_number++;
      }
    }
    reference_ = "RR-" + registration_ + "-" + to_string(reference_number);
    for (int i = rental_list_.size() - 1; i >= 0; i--) {
      if (registration_ == rental_list_[i].GetRentalRegistration()) {
        Date rental_end_date = Date(rental_list_[i].GetRentalEndDate());
        Date rental_start_date = Date(rental_list_[i].GetRentalStartDate());
        if (start_date_ > rental_end_date || rental_start_date > end_date_) {
          Rental new_rental(registration_, start_date_.GetDate(),
                            end_date_.GetDate(), user_id_, reference_);
          rental_list_.push_back(new_rental);

          int duration = CalculateRentalDuration(start_date_, end_date_);

          if (duration > 1) {
            Message::CAR_IS_NOW_RENTED.PrintMessage({registration_, user_id_,
                                                     to_string(duration), "s",
                                                     reference_});
            return;
          } else {
            Message::CAR_IS_NOW_RENTED.PrintMessage(
                {registration_, user_id_, to_string(duration), "", reference_});
            return;
          }
        } else {
          Message::CAR_ALREADY_RENTED.PrintMessage(
              {registration_, rental_list_[i].GetRentalReference()});
          return;
        }
      }
    }
    Rental new_rental(registration_, start_date_.GetDate(), end_date_.GetDate(),
                      user_id_, reference_);
    rental_list_.push_back(new_rental);

    int duration = CalculateRentalDuration(start_date_, end_date_);

    if (duration > 1) {
      Message::CAR_IS_NOW_RENTED.PrintMessage(
          {registration_, user_id_, to_string(duration), "s", reference_});
      return;
    } else {
      Message::CAR_IS_NOW_RENTED.PrintMessage(
          {registration_, user_id_, to_string(duration), "", reference_});
      return;
    }
  }
  for (int i = 0; i < car_list_.size(); i++) {
    for (int j = 0; j < rental_list_.size(); j++) {
      if (car_list_[i].GetRegistrationPlate() ==
          rental_list_[j].GetRentalRegistration()) {
        if (CheckCarAvailability(configured_date_,
                                 rental_list_[j].GetRentalStartDate(),
                                 rental_list_[j].GetRentalEndDate()) == 1) {
          car_list_[i].MakeCarAvailable();
        } else {
          car_list_[i].MakeCarNotAvailable();
        }
      }
    }
  }
}

bool App::CheckForRegistration(const std::string &registration_) const {
  for (int i = 0; i < car_list_.size(); i++) {
    if (car_list_[i].GetRegistrationPlate() == registration_) {
      return 1;
    }
  }
  return 0;
}

bool App::CheckValidStartDate(const Date &start_date) const {
  if (start_date.GetYear() > year1_) {
    return 1;
  } else if (start_date.GetMonth() > month1_ &&
             start_date.GetYear() == year1_) {
    return 1;
  } else if (start_date.GetDay() >= day1_ &&
             start_date.GetMonth() == month1_ &&
             start_date.GetYear() == year1_) {
    return 1;
  } else {
    return 0;
  }
}

bool App::CheckValidEndDate(const Date &end_date) const {
  if (end_date.GetYear() > start_year_) {
    return 1;
  } else if (end_date.GetMonth() > start_month_ &&
             end_date.GetYear() == start_year_) {
    return 1;
  } else if (end_date.GetDay() >= start_day_ &&
             end_date.GetMonth() == start_month_ &&
             end_date.GetYear() == start_year_) {
    return 1;
  } else {
    return 0;
  }
}

int App::CalculateRentalDuration(const Date &start_date,
                                 const Date &end_date) const {
  return (stoi(end_date.GetDate().substr(0, 2)) -
          stoi(start_date.GetDate().substr(0, 2)) + 1);
}

void App::DisplayRentals(const std::string &registration_plate) const {
  std::string plate = registration_plate;
  for (int i = 0; i < plate.length(); i++) {
    plate[i] = toupper(plate[i]);
  }

  if (configured_date_.length() == 0) {
    Message::DATE_NOT_CONFIGURED.PrintMessage();
    return;
  }
  Date system_date(configured_date_);
  int count1 = 0;
  int count2 = 0;
  for (int i = 0; i < car_list_.size(); i++) {
    if (car_list_[i].GetRegistrationPlate() == plate) {
      count2++;
    }
  }

  for (int i = 0; i < rental_list_.size(); i++) {
    if (rental_list_[i].GetRentalRegistration() == plate) {
      Date check_start_date = Date(rental_list_[i].GetRentalStartDate());
      Date check_end_date = Date(rental_list_[i].GetRentalEndDate());
      if (check_end_date >= system_date) {
        int duration =
            CalculateRentalDuration(check_start_date, check_end_date);
        if (duration == 1) {
          Message::LIST_RENTAL_ENTRY.PrintMessage(
              {rental_list_[i].GetRentalStartDate(),
               rental_list_[i].GetRentalEndDate(), to_string(duration), "",
               rental_list_[i].GetRentalReference()});
          count1++;
        } else {
          Message::LIST_RENTAL_ENTRY.PrintMessage(
              {rental_list_[i].GetRentalStartDate(),
               rental_list_[i].GetRentalEndDate(), to_string(duration), "s",
               rental_list_[i].GetRentalReference()});
          count1++;
        }
      }
    }
  }
  if (count2 == 0) {
    Message::NO_CAR_WITH_PLATE.PrintMessage({plate});
    return;
  } else if (count1 == 0) {
    Message::NO_UPCOMING_RENTALS.PrintMessage();
    return;
  }
}

void App::AddGPSUnit(const std::string &rental_reference) {
  std::string upper_rental_reference = rental_reference;
  for (int i = 0; i < upper_rental_reference.length(); i++) {
    upper_rental_reference[i] = toupper(upper_rental_reference[i]);
  }
  for (int i = 0; i < rental_list_.size(); i++) {
    if (rental_list_[i].GetRentalReference() == upper_rental_reference) {
      Date system_date = Date(configured_date_);
      Date start_date_gps = Date(rental_list_[i].GetRentalStartDate());
      Date end_date_gps = Date(rental_list_[i].GetRentalEndDate());
      if (system_date > start_date_gps) {
        Message::CANNOT_ADD_ADDON_IN_PAST.PrintMessage(
            {upper_rental_reference, "GPS Unit"});
        return;
      } else {
        int duration = CalculateRentalDuration(start_date_gps, end_date_gps);
        Gps new_gps_unit(upper_rental_reference, duration);
        gps_list_.push_back(new_gps_unit);
        rental_list_[i].AddGpsUnit();
        Message::ADDON_ADDED.PrintMessage(
            {Message::ADDON_GPS_UNIT_NAME.GetMessage()});
        return;
      }
    }
  }
  Message::CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND.PrintMessage(
      {upper_rental_reference, Message::ADDON_GPS_UNIT_NAME.GetMessage()});
  return;
}

void App::AddChildSeat(const std::string &rental_reference) {
  std::string upper_rental_reference = rental_reference;
  for (int i = 0; i < upper_rental_reference.length(); i++) {
    upper_rental_reference[i] = toupper(upper_rental_reference[i]);
  }
  for (int i = 0; i < rental_list_.size(); i++) {
    if (rental_list_[i].GetRentalReference() == upper_rental_reference) {
      Date system_date = Date(configured_date_);
      Date start_date_child_seat = Date(rental_list_[i].GetRentalStartDate());
      Date end_date_child_seat = Date(rental_list_[i].GetRentalEndDate());
      if (system_date > start_date_child_seat) {
        Message::CANNOT_ADD_ADDON_IN_PAST.PrintMessage(
            {upper_rental_reference,
             Message::ADDON_CHILD_SEAT_NAME.GetMessage()});
        return;
      } else {
        int duration =
            CalculateRentalDuration(start_date_child_seat, end_date_child_seat);
        ChildSeat new_child_seat(upper_rental_reference, duration);
        child_seat_list_.push_back(new_child_seat);
        rental_list_[i].AddChildSeat();
        Message::ADDON_ADDED.PrintMessage(
            {Message::ADDON_CHILD_SEAT_NAME.GetMessage()});
        return;
      }
    }
  }
  Message::CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND.PrintMessage(
      {upper_rental_reference, Message::ADDON_CHILD_SEAT_NAME.GetMessage()});
  return;
}

void App::AddInsurance(const std::string &rental_reference) {
  std::string upper_rental_reference = rental_reference;
  for (int i = 0; i < upper_rental_reference.length(); i++) {
    upper_rental_reference[i] = toupper(upper_rental_reference[i]);
  }
  for (int i = 0; i < rental_list_.size(); i++) {
    if (rental_list_[i].GetRentalReference() == upper_rental_reference) {
      Date system_date = Date(configured_date_);
      Date start_date_insurance = Date(rental_list_[i].GetRentalStartDate());
      Date end_date_insurance = Date(rental_list_[i].GetRentalEndDate());
      if (system_date > start_date_insurance) {
        Message::CANNOT_ADD_ADDON_IN_PAST.PrintMessage(
            {upper_rental_reference,
             Message::ADDON_INSURANCE_NAME.GetMessage()});
        return;
      } else {
        int duration =
            CalculateRentalDuration(start_date_insurance, end_date_insurance);
        for (int j = 0; j < car_list_.size(); j++) {
          if (rental_list_[i].GetRentalRegistration() ==
              car_list_[j].GetRegistrationPlate()) {
            int daily_rental_fee = car_list_[j].GetDailyRentalFee();
            if (duration > 4) {
              int total_rental_cost = ((duration - 4) * (daily_rental_fee / 2) +
                                       (4 * daily_rental_fee));
              Insurance new_insurance(upper_rental_reference, duration,
                                      total_rental_cost);
              insurance_list_.push_back(new_insurance);
              rental_list_[i].AddInsurance();
              Message::ADDON_ADDED.PrintMessage(
                  {Message::ADDON_INSURANCE_NAME.GetMessage()});
              return;
            } else {
              int total_rental_cost = duration * daily_rental_fee;
              Insurance new_insurance(upper_rental_reference, duration,
                                      total_rental_cost);
              insurance_list_.push_back(new_insurance);
              rental_list_[i].AddInsurance();
              Message::ADDON_ADDED.PrintMessage(
                  {Message::ADDON_INSURANCE_NAME.GetMessage()});
              return;
            }
          }
        }
      }
    }
  }
  Message::CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND.PrintMessage(
      {upper_rental_reference, Message::ADDON_INSURANCE_NAME.GetMessage()});
  return;
}

void App::DisplayReceipt(const std::string &rental_reference) const {
  int receipt_total = 0;
  std::string upper_rental_reference = rental_reference;
  for (int i = 0; i < upper_rental_reference.length(); i++) {
    upper_rental_reference[i] = toupper(upper_rental_reference[i]);
  }
  for (int i = 0; i < rental_list_.size(); i++) {
    if (rental_list_[i].GetRentalReference() == upper_rental_reference) {
      std::string receipt_reference = upper_rental_reference;
      std::string receipt_id = rental_list_[i].GetRentalId();
      std::string receipt_pickup = rental_list_[i].GetRentalStartDate();
      std::string receipt_return = rental_list_[i].GetRentalEndDate();
      int duration =
          CalculateRentalDuration(rental_list_[i].GetRentalStartDate(),
                                  rental_list_[i].GetRentalEndDate());
      std::string receipt_duration = to_string(duration);
      Message::RECEIPT_TOP_PART.PrintMessage({receipt_reference, receipt_id,
                                              receipt_pickup, receipt_return,
                                              receipt_duration});
      for (int j = 0; j < car_list_.size(); j++) {
        if (rental_list_[i].GetRentalRegistration() ==
            car_list_[j].GetRegistrationPlate()) {
          int daily_rental_fee = car_list_[j].GetDailyRentalFee();
          if (duration > 4) {
            int total_rental_cost = (4 * daily_rental_fee) +
                                    ((duration - 4) * (daily_rental_fee / 2));
            receipt_total += total_rental_cost;
            std::string receipt_rental_cost = to_string(total_rental_cost);
            Message::RECEIPT_COST_BREAKDOWN_CAR_RENTAL.PrintMessage(
                {receipt_rental_cost});
            break;
          } else {
            int total_rental_cost = duration * daily_rental_fee;
            receipt_total += total_rental_cost;
            std::string receipt_rental_cost = to_string(total_rental_cost);
            Message::RECEIPT_COST_BREAKDOWN_CAR_RENTAL.PrintMessage(
                {receipt_rental_cost});
            break;
          }
        }
      }
      if (rental_list_[i].GetGps() == 1) {
        for (int i = 0; i < gps_list_.size(); i++) {
          if (gps_list_[i].GetReference() == upper_rental_reference) {
            std::string receipt_gps_cost = to_string(gps_list_[i].GetCost());
            receipt_total += gps_list_[i].GetCost();
            Message::RECEIPT_COST_BREAKDOWN_ADDON_ITEM.PrintMessage(
                {Message::ADDON_GPS_UNIT_NAME.GetMessage(), receipt_gps_cost});
            break;
          }
        }
      }
      if (rental_list_[i].GetChildSeat() == 1) {
        for (int i = 0; i < child_seat_list_.size(); i++) {
          if (child_seat_list_[i].GetReference() == upper_rental_reference) {
            std::string receipt_child_seat_cost =
                to_string(child_seat_list_[i].GetCost());
            receipt_total += child_seat_list_[i].GetCost();
            Message::RECEIPT_COST_BREAKDOWN_ADDON_ITEM.PrintMessage(
                {Message::ADDON_CHILD_SEAT_NAME.GetMessage(),
                 receipt_child_seat_cost});
            break;
          }
        }
      }
      if (rental_list_[i].GetInsurance() == 1) {
        for (int i = 0; i < insurance_list_.size(); i++) {
          if (insurance_list_[i].GetReference() == upper_rental_reference) {
            std::string receipt_insurance_cost =
                to_string(insurance_list_[i].GetCost());
            receipt_total += insurance_list_[i].GetCost();
            Message::RECEIPT_COST_BREAKDOWN_ADDON_ITEM.PrintMessage(
                {Message::ADDON_INSURANCE_NAME.GetMessage(),
                 receipt_insurance_cost});
            break;
          }
        }
      }
      Message::RECEIPT_BOTTOM_PART.PrintMessage({to_string(receipt_total)});
      return;
    }
  }

  Message::REFERENCE_NOT_FOUND_NO_RECEIPT.PrintMessage(
      {upper_rental_reference});
  return;
}

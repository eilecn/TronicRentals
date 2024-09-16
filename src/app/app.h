#ifndef APP_H
#define APP_H

#include <string>
#include <vector>

#include "car.h"
#include "childseat.h"
#include "date.h"
#include "gps.h"
#include "insurance.h"
#include "rental.h"

/*
----------------------------------------------------------------------------
  This is where you start.
  However, make sure you do not not write all your code in a single file!
----------------------------------------------------------------------------
*/

class App {
 private:
  std::vector<Car> car_list_;
  std::vector<Rental> rental_list_;
  std::vector<Gps> gps_list_;
  std::vector<ChildSeat> child_seat_list_;
  std::vector<Insurance> insurance_list_;
  std::string reference_;
  std::string configured_date_;
  int day1_;
  int month1_;
  int year1_;
  int day2_;
  int month2_;
  int year2_;
  std::string registration_;
  std::string start_date_;
  std::string end_date_;
  std::string user_id_;
  int start_day_;
  int start_month_;
  int start_year_;

 public:
  App();
  void CreateCar(const std::string &registration_plate, const std::string &make,
                 const std::string &daily_rental_fee);
  void DisplayCars() const;
  void ConfigureDate(const std::string &date);
  void DisplayDate() const;
  void CreateRental(const std::vector<std::string> options);
  void DisplayRentals(const std::string &registration_plate) const;
  void AddGPSUnit(const std::string &rental_reference);
  void AddChildSeat(const std::string &rental_reference);
  void AddInsurance(const std::string &rental_reference);
  void DisplayReceipt(const std::string &rental_reference) const;
  bool CheckCarAvailability(const std::string &system_date,
                            const std::string start_date,
                            const std::string end_date) const;
  bool CheckForRegistration(const std::string &registration) const;
  bool CheckValidStartDate(const Date &start_date) const;
  bool CheckValidEndDate(const Date &end_date) const;
  int CalculateRentalDuration(const Date &start_date,
                              const Date &end_date) const;
};

#endif  // APP_H

#ifndef RENTAL_H
#define RENTAL_H
#include <string>
#include <vector>

class Rental {
 public:
  Rental(const std::string &registration, const std::string &start_date,
         const std::string &end_date, const std::string &user_id,
         const std::string &reference);
  std::string GetRentalStartDate() const;
  std::string GetRentalEndDate() const;
  std::string GetRentalRegistration() const;
  std::string GetRentalReference() const;
  std::string GetRentalId() const;
  void AddGpsUnit();
  void AddChildSeat();
  void AddInsurance();
  bool GetGps() const;
  bool GetChildSeat() const;
  bool GetInsurance() const;

 private:
  std::string rental_registration_;
  std::string rental_start_;
  std::string rental_end_;
  std::string rental_id_;
  std::string rental_reference_;
  bool gps_;
  bool child_seat_;
  bool insurance_;
};

#endif

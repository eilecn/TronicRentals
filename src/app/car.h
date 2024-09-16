#ifndef CAR_H
#define CAR_H
#include <string>

class Car {
 public:
  Car(const std::string &registration_plate, const std::string &make,
      const std::string &daily_rental_fee);
  void DisplayCarInfo() const;
  std::string GetRegistrationPlate() const;
  bool CheckValidPlate();
  void PrintMakeFormat();
  bool CheckValidFee();
  bool GetAvailability() const;
  void MakeCarAvailable();
  void MakeCarNotAvailable();
  int GetDailyRentalFee() const;

 private:
  std::string registration_plate_;
  std::string make_;
  std::string daily_rental_fee_;
  bool availability_;
};

#endif

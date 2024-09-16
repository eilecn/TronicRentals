#if !defined(MESSAGE_H)
#define MESSAGE_H

#include <initializer_list>
#include <string>

/*
**********************************************************************************
  DO NOT MODIFY THIS FILE.
  During marking, we will use the original version of this file that we
    provided. If you change the file, the automated tests will fail and you will
    most likely lose marks.
**********************************************************************************
*/

class Message {
 private:
  std::string msg_;

 public:
  static const Message NO_CARS_AVAILABLE;
  static const Message CAR_CREATED;
  static const Message CAR_ALREADY_EXISTS;
  static const Message NUMBER_OF_CARS_AVAILABLE;
  static const Message INVALID_REGISTRATION_PLATE;
  static const Message LIST_CAR_ENTRY;
  static const Message NO_CAR_WITH_PLATE;
  static const Message CAR_IS_NOW_RENTED;
  static const Message CAR_ALREADY_RENTED;
  static const Message RENTAL_FEE_NOT_POSITIVE;
  static const Message RENTAL_FEE_MUST_BE_NUMERIC;
  static const Message NO_UPCOMING_RENTALS;
  static const Message LIST_RENTAL_ENTRY;
  static const Message DATE_NOT_CONFIGURED;
  static const Message DATE_CONFIGURED;
  static const Message DATE_CURRENTLY;
  static const Message DATE_BEFORE_CURRENT;
  static const Message START_DATE_BEFORE_TODAY;
  static const Message END_DATE_BEFORE_START;
  static const Message ADDON_GPS_UNIT_NAME;
  static const Message ADDON_CHILD_SEAT_NAME;
  static const Message ADDON_INSURANCE_NAME;
  static const Message CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND;
  static const Message CANNOT_ADD_ADDON_IN_PAST;
  static const Message ADDON_ADDED;
  static const Message REFERENCE_NOT_FOUND_NO_RECEIPT;
  static const Message RECEIPT_TOP_PART;
  static const Message RECEIPT_COST_BREAKDOWN_CAR_RENTAL;
  static const Message RECEIPT_COST_BREAKDOWN_ADDON_ITEM;
  static const Message RECEIPT_BOTTOM_PART;

  static const Message COMMAND_NOT_FOUND;
  static const Message WRONG_ARGUMENT_COUNT;
  static const Message WRONG_OPTION_COUNT;
  static const Message END;

  Message(const std::string &msg);
  std::string GetMessage() const;
  std::string GetMessage(std::initializer_list<std::string> args) const;
  void PrintMessage() const;
  void PrintMessage(std::initializer_list<std::string> args) const;
};

#endif  // MESSAGE_H

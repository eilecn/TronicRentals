#include "message.h"

#include <iostream>

using namespace std;

/*
**********************************************************************************
  DO NOT MODIFY THIS FILE.
  During marking, we will use the original version of this file that we
    provided. If you change the file, the automated tests will fail and you will
    most likely lose marks.
**********************************************************************************
*/

const Message Message::NO_CARS_AVAILABLE("No cars available.");
const Message Message::CAR_CREATED("Car with registration plate '%s' created.");
const Message Message::CAR_ALREADY_EXISTS(
    "Car with registration plate '%s' already exists.");
const Message Message::NUMBER_OF_CARS_AVAILABLE(
    "There %s %s car%s in the system:");
const Message Message::NO_CAR_WITH_PLATE(
    "There is no car with the registration plate '%s'.");
const Message Message::CAR_IS_NOW_RENTED(
    "Car with registration plate '%s' is now rented to '%s' for %s day%s with "
    "reference number '%s'.");
const Message Message::CAR_ALREADY_RENTED(
    "Car with registration plate '%s' is already rented at this time (%s).");

const Message Message::INVALID_REGISTRATION_PLATE(
    "Invalid registration plate '%s'. Car not created.");

const Message Message::LIST_CAR_ENTRY("  * '%s' - %s, $%s/day,%s available");

const Message Message::RENTAL_FEE_NOT_POSITIVE(
    "Rental fee must be greater than 0. Car not created.");
const Message Message::RENTAL_FEE_MUST_BE_NUMERIC(
    "Rental fee must be numeric. Car not created.");
const Message Message::NO_UPCOMING_RENTALS("No upcoming rentals.");
const Message Message::LIST_RENTAL_ENTRY("  * %s - %s (%s day%s) - %s");

const Message Message::DATE_NOT_CONFIGURED("Date has not been configured.");
const Message Message::DATE_CONFIGURED("Date configured to '%s'.");
const Message Message::DATE_CURRENTLY("Current system date is '%s'.");
const Message Message::DATE_BEFORE_CURRENT(
    "Cannot configure to a date before the current date.");
const Message Message::START_DATE_BEFORE_TODAY(
    "Start date must be today (%s) or later.");
const Message Message::END_DATE_BEFORE_START(
    "End date must be on or after the start date (%s).");

const Message Message::ADDON_GPS_UNIT_NAME("GPS Unit");
const Message Message::ADDON_CHILD_SEAT_NAME("Child Seat");
const Message Message::ADDON_INSURANCE_NAME("Insurance");

const Message Message::CANNOT_ADD_ADDON_REFERENCE_NOT_FOUND(
    "Rental reference '%s' not found, %s not added.");
const Message Message::CANNOT_ADD_ADDON_IN_PAST(
    "Rental '%s' is in the past, too late to add %s.");
const Message Message::ADDON_ADDED("%s added to rental.");

const Message Message::REFERENCE_NOT_FOUND_NO_RECEIPT(
    "Rental reference '%s' not found, no receipt to display.");

const Message Message::RECEIPT_TOP_PART(
    "\n===============================================================\n"
    "                           RECEIPT\n"
    "             -------------------------------------\n\n"
    "Booking Reference: %s\n\n"
    "Booking Details:\n"
    "  Customer ID: %s\n\n"
    "Rental Details:\n"
    "  Pickup Date: %s\n"
    "  Return Date: %s\n"
    "  Number of Days: %s\n\n"
    "Cost Breakdown:");

const Message Message::RECEIPT_COST_BREAKDOWN_CAR_RENTAL("  Car Rental: $%s");
const Message Message::RECEIPT_COST_BREAKDOWN_ADDON_ITEM("  %s Add-on: $%s");

const Message Message::RECEIPT_BOTTOM_PART(
    "\nGRAND TOTAL: $%s\n\n"
    "Thank you for choosing TronicRentals!\n"
    "For any inquiries, please contact support@tronicrentals.co.nz"
    "\n===============================================================\n");

const Message Message::COMMAND_NOT_FOUND(
    "Command '%s' not found. Run 'help' for the list of available commands.");
const Message Message::WRONG_ARGUMENT_COUNT(
    "Incorrect number of arguments for %s. Expected %s, but %s provided.");
const Message Message::WRONG_OPTION_COUNT(
    "Incorrect number of options for %s. Expected %s, but %s provided.");
const Message Message::END("Program ended.");

Message::Message(const std::string &msg) { this->msg_ = msg; }

std::string Message::GetMessage() const { return GetMessage({}); }

std::string Message::GetMessage(std::initializer_list<std::string> args) const {
  std::string result = msg_;
  for (const string &arg : args) {
    size_t pos = result.find("%s");
    if (pos != std::string::npos) {
      result.replace(pos, 2, arg);
    }
  }
  return result;
}

void Message::PrintMessage() const { PrintMessage({}); }

void Message::PrintMessage(std::initializer_list<std::string> args) const {
  cout << GetMessage(args) << endl;
}

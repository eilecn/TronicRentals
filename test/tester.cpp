#include <algorithm>
#include <cctype>
#include <cstring>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app/launcher.h"
#include "app/utils.h"

using namespace std;

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  DO NOT MODIFY EXISTING METHODS. You may add additional test cases if you wish.
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

enum TestResult { TEST_RESULT_PASS, TEST_RESULT_FAIL };

#include <sstream>
#include <string>
#include <vector>

#define RUN_COMMAND(command_with_args)                           \
  cout << app.GetCommandPrefix() << command_with_args << "\n\r"; \
  app.ProcessCommand(command_with_args);

#define RUN_COMMAND_WITH_OPTIONS(command_with_args, options_str)              \
  {                                                                           \
    std::vector<std::string> _options = Utils::SplitString(options_str, ";"); \
    cout << app.GetCommandPrefix() << command_with_args << "\n\r";            \
    app.ProcessCommand(command_with_args, _options);                          \
  }

#define __FILENAME__ \
  (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXPECT_CONTAINS(expected)                                              \
  if (still_capturing_cout) {                                                  \
    still_capturing_cout = false;                                              \
    output = replaceNewlineWithCRLF(buffer.str());                             \
    std::cout.rdbuf(old);                                                      \
    std::cout << output << "\n\r";                                             \
  }                                                                            \
  if (output.find(expected) == std::string::npos) {                            \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__            \
         << " on line " << __LINE__ << ":\n\r" << "  Expected '" << expected   \
         << "' in the output, but it was not found." << "\n\r" << "\n\r"       \
         << "----------------------------------------------------------------" \
            "------------"                                                     \
         << "\n\r" << "\n\r";                                                  \
    return TEST_RESULT_FAIL;                                                   \
  }

#define EXPECT_DOES_NOT_CONTAINS(expected, ignore_case)                      \
  output = replaceNewlineWithCRLF(buffer.str());                             \
  if (Utils::Contains(output, expected, ignore_case)) {                      \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__          \
         << " on line " << __LINE__ << ":\n\r" << "\tExpected '" << expected \
         << "' to NOT be in the output, but it was." << "\n\r" << "\n\r";    \
    return TEST_RESULT_FAIL;                                                 \
  }

std::string replaceNewlineWithCRLF(const std::string &input) {
  std::string replacedStr;
  for (char ch : input) {
    if (ch == '\n') {
      replacedStr += "\n\r";
    } else {
      replacedStr += ch;
    }
  }
  return replacedStr;
}

int main(int argc, char *argv[]) {
  Launcher app;
  string output = "";
  bool still_capturing_cout = true;
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  int test_number = std::stoi(argv[1]);
  switch (test_number) {
    case 1:  // Task_1_ZeroCars
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("No cars available.");
      EXPECT_DOES_NOT_CONTAINS("There is", true);

      break;
    case 2:  // Task_1_CreateNewCar
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 3:  // Task_1_CreateNewCarWithDisplay
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_CONTAINS("There is 1 car in the system:");
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 5:  // Task_1_CreateMultipleCarsWithDisplay
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
      RUN_COMMAND("CREATE_CAR GHI789 Ford 300");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_CONTAINS("Car with registration plate 'DEF456' created.");
      EXPECT_CONTAINS("Car with registration plate 'GHI789' created.");
      EXPECT_CONTAINS("There are 3 cars in the system:");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("0 car", true);
      EXPECT_DOES_NOT_CONTAINS("1 car", true);
      EXPECT_DOES_NOT_CONTAINS("2 car", true);

      break;
    case 6:  // Task_1_CreateCarWithInvalidRegistrationPlateLength
      RUN_COMMAND("CREATE_CAR ABC1234 Toyota 100");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Invalid registration plate 'ABC1234'. Car not created.");
      EXPECT_CONTAINS("No cars available.");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 8:  // Task_1_CreateCarWithInvalidRegistrationPlateAllLetters
      RUN_COMMAND("CREATE_CAR ABCDEF Toyota 100");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Invalid registration plate 'ABCDEF'. Car not created.");
      EXPECT_CONTAINS("No cars available.");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 11:  // Task_1_CreateCarWithRegistrationPlateLowerCase
      RUN_COMMAND("CREATE_CAR abc123 Toyota 100");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_CONTAINS("There is 1 car in the system:");
      EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, available");
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 13:  // Task_1_CreateCarRentalFeeZero
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 0");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Rental fee must be greater than 0. Car not created.");
      EXPECT_CONTAINS("No cars available.");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("There are", true);

      break;
    case 17:  // Task_1_CreateCarWithDuplicateMake
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Toyota 200");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_CONTAINS("Car with registration plate 'DEF456' created.");
      EXPECT_CONTAINS("There are 2 cars in the system:");
      EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, available");
      EXPECT_CONTAINS("* 'DEF456' - Toyota, $200/day, available");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("already exists", true);

      break;
    case 18:  // Task_1_CreateCarWithDuplicateRentalFee
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 100");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
      EXPECT_CONTAINS("Car with registration plate 'DEF456' created.");
      EXPECT_CONTAINS("There are 2 cars in the system:");
      EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, available");
      EXPECT_CONTAINS("* 'DEF456' - Honda, $100/day, available");
      EXPECT_DOES_NOT_CONTAINS("There is", true);
      EXPECT_DOES_NOT_CONTAINS("already exists", true);

      break;
    case 21:  // Task_2_DisplayDateNotConfigured
      RUN_COMMAND("DISPLAY_DATE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date has not been configured.");
      EXPECT_DOES_NOT_CONTAINS("Current system date is", true);

      break;
    case 22:  // Task_2_ConfigureDateWithoutDisplay
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date configured to '01/01/2024'.");
      EXPECT_DOES_NOT_CONTAINS("Current system date is", true);

      break;
    case 23:  // Task_2_ConfigureDate
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("DISPLAY_DATE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date configured to '01/01/2024'.");
      EXPECT_CONTAINS("Current system date is '01/01/2024'.");
      EXPECT_DOES_NOT_CONTAINS("Date has not been configured.", true);

      break;
    case 24:  // Task_2_ConfigureWeirdDate
      RUN_COMMAND("CONFIGURE_DATE 35/02/2024");
      RUN_COMMAND("DISPLAY_DATE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date configured to '35/02/2024'.");
      EXPECT_CONTAINS("Current system date is '35/02/2024'.");
      EXPECT_DOES_NOT_CONTAINS("Date has not been configured.", true);

      break;
    case 27:  // Task_2_ReconfigureDateInvalidYesterday
      RUN_COMMAND("CONFIGURE_DATE 25/06/2024");
      RUN_COMMAND("CONFIGURE_DATE 24/06/2024");
      RUN_COMMAND("DISPLAY_DATE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date configured to '25/06/2024'.");
      EXPECT_CONTAINS("Cannot configure to a date before the current date.");
      EXPECT_CONTAINS("Current system date is '25/06/2024'.");
      EXPECT_DOES_NOT_CONTAINS("Current system date is '24/06/2024'.", true);

      break;
    case 28:  // Task_2_ReconfigureDateInvalidLastMonth
      RUN_COMMAND("CONFIGURE_DATE 25/06/2024");
      RUN_COMMAND("CONFIGURE_DATE 25/05/2024");
      RUN_COMMAND("DISPLAY_DATE");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date configured to '25/06/2024'.");
      EXPECT_CONTAINS("Cannot configure to a date before the current date.");
      EXPECT_CONTAINS("Current system date is '25/06/2024'.");
      EXPECT_DOES_NOT_CONTAINS("Current system date is '25/05/2024'.", true);

      break;
    case 32:  // Task_2_CreateRentalNoCars
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/01/2024;01/02/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("There is no car with the registration plate 'ABC123'.");
      EXPECT_DOES_NOT_CONTAINS("is now rented", true);

      break;
    case 34:  // Task_2_CreateRentalSimple
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/01/2024;01/02/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Car with registration plate 'ABC123' is now rented");
      EXPECT_DOES_NOT_CONTAINS("There is no car", true);

      break;
    case 37:  // Task_2_CreateRentalSimpleWithDaysCalculated
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/01/2024;02/01/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("is now rented to");
      EXPECT_CONTAINS("for 2 days");
      EXPECT_DOES_NOT_CONTAINS("There is no car", true);

      break;
    case 38:  // Task_2_CreateRentalSimpleWithReferenceNumber
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/01/2024;02/01/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("is now rented to");
      EXPECT_CONTAINS(" with reference number 'RR-ABC123-1'");
      EXPECT_DOES_NOT_CONTAINS("There is no car", true);

      break;
    case 39:  // Task_2_CreateRentalSimpleCompleteMessage
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/01/2024;03/01/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "Car with registration plate 'ABC123' is now rented to "
          "'nasser' for 3 days with reference number 'RR-ABC123-1'.");
      EXPECT_DOES_NOT_CONTAINS("There is no car", true);

      break;
    case 41:  // Task_2_CreateRentalSimpleCompleteMessageFutureDateNextMonth
      RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;12/02/2024;12/02/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "Car with registration plate 'ABC123' is now rented to "
          "'nasser' for 1 day with reference number 'RR-ABC123-1'.");
      EXPECT_DOES_NOT_CONTAINS("There is no car", true);

      break;
    case 44:  // Task_2_CreateRentalEndDateBeforeStartDate
      RUN_COMMAND("CONFIGURE_DATE 11/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;12/11/2024;Nasser");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "End date must be on or after the start date (14/11/2024).");
      EXPECT_DOES_NOT_CONTAINS("is now rented", true);

      break;
    case 46:  // Task_2_CreateRentalCarAlreadyRentedSameDayFuture
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;14/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;14/11/2024;Luke");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("is now rented to 'nasser' for 1 day with reference");
      EXPECT_CONTAINS(
          "Car with registration plate 'ABC123' is already rented at this time "
          "(RR-ABC123-1).");
      EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
      EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);

      break;
    case 47:  // Task_2_CreateRentalCarAlreadyRentedSameDateRange
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Luke");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("is now rented to 'nasser' for 3 days with reference");
      EXPECT_CONTAINS(
          "Car with registration plate 'ABC123' is already rented at this time "
          "(RR-ABC123-1).");
      EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
      EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);

      break;
    case 52:  // Task_2_CreateRentalSameCarDifferentDates
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/12/2024;16/12/2024;Luke");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "is now rented to 'nasser' for 3 days with reference number "
          "'RR-ABC123-1'");
      EXPECT_CONTAINS(
          "is now rented to 'luke' for 3 days with reference number "
          "'RR-ABC123-2'");

      EXPECT_DOES_NOT_CONTAINS("is already rented", true);

      break;
    case 54:  // Task_2_DisplayRentalsNotConfigured
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Date has not been configured.");
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 57:  // Task_2_DisplayRentalsSingleRental
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 14/11/2024 - 16/11/2024 (3 days) - RR-ABC123-1");
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 58:  // Task_2_DisplayRentalsSingleRentalDifferentCarDisplayRented
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 14/11/2024 - 16/11/2024 (3 days) - RR-ABC123-1");
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 60:  // Task_2_DisplayRentalsMultipleRentalsDifferentCars
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "DEF456;14/12/2024;18/12/2024;Luke");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("DISPLAY_RENTALS DEF456");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 14/11/2024 - 16/11/2024 (3 days) - RR-ABC123-1");
      EXPECT_CONTAINS("* 14/12/2024 - 18/12/2024 (5 days) - RR-DEF456-1");
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 62:  // Task_2_DisplayRentalAfterSystemDateChange
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;18/11/2024;20/11/2024;Nasser");
      RUN_COMMAND("CONFIGURE_DATE 15/11/2024");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 18/11/2024 - 20/11/2024 (3 days) - RR-ABC123-1");
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 63:  // Task_2_DisplayRentalsMultipleRentalsSameCarDifferentDatesAfterSystemDateChange
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;18/11/2024;20/11/2024;Luke");
      RUN_COMMAND("CONFIGURE_DATE 17/11/2024");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 18/11/2024 - 20/11/2024 (3 days) - RR-ABC123-2");
      EXPECT_DOES_NOT_CONTAINS("* 14/11/2024 - 16/11/2024", true);
      EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

      break;
    case 65:  // Task_2_DisplayRentalsMultipleRentalsDifferentCarsAfterSystemDateChangeFarInFuture
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;16/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;01/12/2024;03/12/2024;Jenny");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "DEF456;14/12/2024;18/12/2024;Luke");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "DEF456;14/12/2025;16/12/2025;Mary");
      RUN_COMMAND("CONFIGURE_DATE 17/11/2030");
      RUN_COMMAND("DISPLAY_RENTALS ABC123");
      RUN_COMMAND("DISPLAY_RENTALS DEF456");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("No upcoming rentals");
      EXPECT_DOES_NOT_CONTAINS("days) - RR-ABC123-1", true);
      EXPECT_DOES_NOT_CONTAINS("days) - RR-ABC123-2", true);
      EXPECT_DOES_NOT_CONTAINS("days) - RR-DEF456-1", true);
      EXPECT_DOES_NOT_CONTAINS("days) - RR-DEF456-2", true);

      break;
    case 66:  // Task_2_Display_Car_Available_Today
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2024;15/11/2024;Nasser");
      RUN_COMMAND("CONFIGURE_DATE 13/11/2024");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("CONFIGURE_DATE 16/11/2024");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, available");
      EXPECT_DOES_NOT_CONTAINS("not available", true);

      break;
    case 69:  // Task_2_Display_Cars_All_Not_Available_Today
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;13/11/2024;15/11/2024;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "DEF456;13/11/2024;15/11/2024;Nasser");
      RUN_COMMAND("CONFIGURE_DATE 13/11/2024");
      RUN_COMMAND("DISPLAY_CARS");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, not available");
      EXPECT_CONTAINS("* 'DEF456' - Honda, $200/day, not available");
      EXPECT_DOES_NOT_CONTAINS(", available", true);

      break;
    case 71:  // Task_3_AddGpsUnitRentalNotFound
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "Rental reference 'RR-ABC123-1' not found, GPS Unit not "
          "added.");
      EXPECT_DOES_NOT_CONTAINS("GPS Unit added to rental", true);

      break;
    case 72:  // Task_3_AddGpsUnitRentalAlreadyStarted
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("CONFIGURE_DATE 11/11/2025");
      RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "Rental 'RR-ABC123-1' is in the past, too late to add GPS Unit.");
      EXPECT_DOES_NOT_CONTAINS("GPS Unit added to rental", true);

      break;
    case 73:  // Task_3_AddCarSeatOk
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");

      RUN_COMMAND("CONFIGURE_DATE 12/09/2025");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Child Seat added to rental");
      EXPECT_DOES_NOT_CONTAINS("not added", true);

      break;
    case 76:  // Task_3_DisplayReceiptRentalNotFound
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS(
          "Rental reference 'RR-ABC123-1' not found, no receipt to "
          "display.");
      EXPECT_DOES_NOT_CONTAINS("Pickup Date:", true);
      EXPECT_DOES_NOT_CONTAINS("Cost Breakdown:", true);
      EXPECT_DOES_NOT_CONTAINS("GRAND TOTAL", true);

      break;
    case 78:  // Task_3_DisplayReceiptRental
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Customer ID: nasser");
      EXPECT_CONTAINS("Pickup Date: 10/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 3");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    case 79:  // Task_3_DisplayReceiptRentalWithCarCost
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 10/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 3");
      EXPECT_CONTAINS("Car Rental: $300");
      EXPECT_CONTAINS("GRAND TOTAL: $300");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    case 81:  // Task_3_DisplayReceiptRentalWithGpsUnit
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;11/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 11/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 2");
      EXPECT_CONTAINS("Car Rental: $200");
      EXPECT_CONTAINS("GPS Unit Add-on: $10");
      EXPECT_CONTAINS("GRAND TOTAL: $210");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    case 84:  // Task_3_DisplayReceiptRentalWithCarSeatDiscounted
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;11/11/2025;19/11/2025;Nasser");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");

      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 11/11/2025");
      EXPECT_CONTAINS("Return Date: 19/11/2025");
      EXPECT_CONTAINS("Number of Days: 9");
      EXPECT_CONTAINS("Car Rental: $650");
      EXPECT_CONTAINS("Child Seat Add-on: $10");
      EXPECT_CONTAINS("GRAND TOTAL: $660");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);
      EXPECT_DOES_NOT_CONTAINS("$18", true);

      break;
    case 85:  // Task_3_DisplayReceiptRentalWithCarSeatDifferentRentals
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;11/11/2025;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2025;16/11/2025;Luke");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-2");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 10/11/2025");
      EXPECT_CONTAINS("Return Date: 11/11/2025");
      EXPECT_CONTAINS("Number of Days: 2");
      EXPECT_CONTAINS("Car Rental: $200");
      EXPECT_CONTAINS("Child Seat Add-on: $4");
      EXPECT_CONTAINS("GRAND TOTAL: $204");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);
      EXPECT_DOES_NOT_CONTAINS("Car Rental: $300", true);
      EXPECT_DOES_NOT_CONTAINS("Child Seat Add-on: $10", true);
      EXPECT_DOES_NOT_CONTAINS("Child Seat Add-on: $12", true);
      EXPECT_DOES_NOT_CONTAINS("GRAND TOTAL: $312", true);

      break;
    case 86:  // Task_3_DisplayReceiptRentalWithInsurance
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;11/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 11/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 2");
      EXPECT_CONTAINS("Car Rental: $200");
      EXPECT_CONTAINS("Insurance Add-on: $10");
      EXPECT_CONTAINS("GRAND TOTAL: $210");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    case 87:  // Task_3_DisplayReceiptRentalWithInsuranceDiscountedCarCost
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;11/11/2025;20/11/2025;Nasser");
      RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 11/11/2025");
      EXPECT_CONTAINS("Return Date: 20/11/2025");
      EXPECT_CONTAINS("Number of Days: 10");
      EXPECT_CONTAINS("Car Rental: $700");
      EXPECT_CONTAINS("Insurance Add-on: $35");
      EXPECT_CONTAINS("GRAND TOTAL: $735");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);
      EXPECT_DOES_NOT_CONTAINS("$1000", true);
      EXPECT_DOES_NOT_CONTAINS("$50", true);

      break;
    case 89:  // Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsurance
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;11/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
      RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 11/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 2");
      EXPECT_CONTAINS("Car Rental: $200");
      EXPECT_CONTAINS("GPS Unit Add-on: $10");
      EXPECT_CONTAINS("Child Seat Add-on: $4");
      EXPECT_CONTAINS("Insurance Add-on: $10");
      EXPECT_CONTAINS("GRAND TOTAL: $224");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    case 91:  // Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsuranceDifferentRentals
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;11/11/2025;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2025;16/11/2025;Luke");
      RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-2");
      RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 10/11/2025");
      EXPECT_CONTAINS("Return Date: 11/11/2025");
      EXPECT_CONTAINS("Number of Days: 2");
      EXPECT_CONTAINS("Car Rental: $200");
      EXPECT_CONTAINS("GPS Unit Add-on: $10");
      EXPECT_CONTAINS("Insurance Add-on: $10");
      EXPECT_CONTAINS("GRAND TOTAL: $220");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);
      EXPECT_DOES_NOT_CONTAINS("Car Rental: $300", true);
      EXPECT_DOES_NOT_CONTAINS("GPS Unit Add-on: $15", true);
      EXPECT_DOES_NOT_CONTAINS("Child Seat Add-on: $6", true);
      EXPECT_DOES_NOT_CONTAINS("Insurance Add-on: $15", true);
      EXPECT_DOES_NOT_CONTAINS("GRAND TOTAL: $336", true);

      break;
    case 94:  // Task_3_AddCarSeatDifferentRentals
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;14/11/2025;23/11/2025;Luke");
      RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-2");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 14/11/2025");
      EXPECT_CONTAINS("Return Date: 23/11/2025");
      EXPECT_CONTAINS("Number of Days: 10");
      EXPECT_CONTAINS("Car Rental: $700");
      EXPECT_CONTAINS("GRAND TOTAL: $700");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-2' not found",
                               true);
      EXPECT_DOES_NOT_CONTAINS("Child Seat cost", true);

      break;
    case 98:  // Task_3_DisplayReceiptRentalActive
      RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
      RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
      RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                               "ABC123;10/11/2025;12/11/2025;Nasser");
      RUN_COMMAND("CONFIGURE_DATE 11/11/2025");
      RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
      RUN_COMMAND("EXIT");

      EXPECT_CONTAINS("Pickup Date: 10/11/2025");
      EXPECT_CONTAINS("Return Date: 12/11/2025");
      EXPECT_CONTAINS("Number of Days: 3");
      EXPECT_CONTAINS("Car Rental: $300");
      EXPECT_CONTAINS("GRAND TOTAL: $300");

      EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                               true);

      break;
    default:
      cerr << "Test case not found: #" << test_number << "\n\r";
      return TEST_RESULT_FAIL;
  }

  cerr << "PASSED Test " << test_number << "." << "\n\r" << "\n\r"
       << "--------------------------------------------------------------------"
          "--------"
       << "\n\r" << "\n\r";
  return TEST_RESULT_PASS;
}

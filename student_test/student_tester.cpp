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

  // Return 0 to allow for the header test case to always pass
  if (test_number == 0) {
    RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
    RUN_COMMAND("EXIT");

    EXPECT_CONTAINS("ABC123");
  } else {
    switch (test_number / 100) {
      case 0:
        switch (test_number % 100) {
          case 1:  // Task_1_CreateMultipleNewCars
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND("CREATE_CAR XYZ789 Honda 200");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
            EXPECT_CONTAINS("Car with registration plate 'XYZ789' created.");
            break;

          case 2:  // Task_1_CreateCarWithInvalidRegistrationPlateAllNumbers
            RUN_COMMAND("CREATE_CAR 123456 Toyota 100");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Invalid registration plate '123456'. Car not created.");
            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate '123456' created.", true);
            break;
          case 3:  // Task_1_CreateCarWithInvalidRegistrationPlateToShort
            RUN_COMMAND("CREATE_CAR ABC12 Toyota 100");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Invalid registration plate 'ABC12'. Car not created.");
            EXPECT_CONTAINS("No cars available.");
            EXPECT_DOES_NOT_CONTAINS("There is", true);
            EXPECT_DOES_NOT_CONTAINS("There are", true);
            break;

          case 4:  // Task_1_CreateInvalidCarWithLowercaseNumberPlate
            RUN_COMMAND("CREATE_CAR abcd23 Toyota 100");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Invalid registration plate 'ABCD23'. Car not created.");
            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate 'abcd23' created.", true);
            EXPECT_DOES_NOT_CONTAINS("abcd123", true);

            break;

          case 5:  // Task_1_CreateCarWithInvalidRentalFeeNotNumeric
            RUN_COMMAND("CREATE_CAR ABC123 Toyota one");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Rental fee must be numeric. Car not created.");
            EXPECT_CONTAINS("No cars available.");
            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate 'ABC123' created.", true);

            break;

          case 6:  // Task_1_CreateCarWithInvalidRentalFeeNotPositive
            RUN_COMMAND("CREATE_CAR ABC123 Toyota -12");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental fee must be greater than 0. Car not created.");
            EXPECT_CONTAINS("No cars available.");
            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate 'ABC123' created.", true);
            break;

          case 7:  // Task_1_CreateCarWithLowerCaseMake
            RUN_COMMAND("CREATE_CAR ABC123 toyota 100");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
            EXPECT_CONTAINS("There is 1 car in the system:");
            EXPECT_CONTAINS("  * 'ABC123' - Toyota, $100/day, available");
            EXPECT_DOES_NOT_CONTAINS("- toyota", false);
            EXPECT_DOES_NOT_CONTAINS("There are", true);
            break;

          case 8:  // Task_1_DisplayCarsWithLowerCaseRegistrationPlate
            RUN_COMMAND("CREATE_CAR abc123 Toyota 100");
            RUN_COMMAND("CREATE_CAR bca123 Honda 200");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
            EXPECT_CONTAINS("Car with registration plate 'BCA123' created.");

            EXPECT_CONTAINS("There are 2 cars in the system:");
            EXPECT_CONTAINS("  * 'ABC123' - Toyota, $100/day, available");
            EXPECT_DOES_NOT_CONTAINS("There is", true);
            EXPECT_DOES_NOT_CONTAINS("'abc123'", false);
            EXPECT_DOES_NOT_CONTAINS("'bca123'", false);
            break;
          case 11:  // Task_1_CreateCarWithDuplicateRegistrationPlate
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND("CREATE_CAR ABC123 Honda 200");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Car with registration plate 'ABC123' created.");
            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' already exists.");
            EXPECT_CONTAINS("There is 1 car in the system:");
            EXPECT_DOES_NOT_CONTAINS("There are", true);
            break;

          default:
            cerr << "Test case not found: #" << test_number / 100 << "-"
                 << test_number % 100 << "\n\r";
            return TEST_RESULT_FAIL;
        }
        break;
      case 1:
        switch (test_number % 100) {
          case 1:  // Task_2_ConfigureDateSameDayAsCurrentDate
            RUN_COMMAND("CONFIGURE_DATE 25/06/2024");
            RUN_COMMAND("CONFIGURE_DATE 25/06/2024");
            RUN_COMMAND("DISPLAY_DATE");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Date configured to '25/06/2024'.");
            EXPECT_DOES_NOT_CONTAINS(
                "Cannot configure to a date before the current date.", true);
            EXPECT_CONTAINS("Current system date is '25/06/2024'.");
            EXPECT_DOES_NOT_CONTAINS("Current system date is '24/06/2024'.",
                                     true);
            break;
          case 2:  // Task_2_ConfigureDateInvalidLastYear
            RUN_COMMAND("CONFIGURE_DATE 25/06/2024");
            RUN_COMMAND("CONFIGURE_DATE 26/07/2023");
            RUN_COMMAND("DISPLAY_DATE");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Date configured to '25/06/2024'.");
            EXPECT_CONTAINS(
                "Cannot configure to a date before the current date.");
            EXPECT_CONTAINS("Current system date is '25/06/2024'.");
            EXPECT_DOES_NOT_CONTAINS("Current system date is '26/07/2023'.",
                                     true);
            break;
          case 6:  // Task_2_CreateRentalDateNotConfigured
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;01/01/2024;01/02/2024;Nasser");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Date has not been configured.");
            EXPECT_DOES_NOT_CONTAINS("is now rented", true);

            break;

          case 7:  // Task_2_CreateRentalStartsInPast
            RUN_COMMAND("CONFIGURE_DATE 03/01/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;01/01/2024;12/02/2024;Nasser");
            RUN_COMMAND("DISPLAY_RENTALS ABC123");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Start date must be today (03/01/2024) or later.");
            EXPECT_CONTAINS("No upcoming rentals");

            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate 'ABC123' is now rented to "
                "'nasser' for 12 day with reference number 'RR-ABC123-1'.",
                true);
            EXPECT_DOES_NOT_CONTAINS("There is no car", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-1", true);

            break;

          case 8:  // Task_2_CreateRentalStartsOnSystemTime
            RUN_COMMAND("CONFIGURE_DATE 03/01/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;03/01/2024;12/02/2024;Nasser");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is now rented to "
                "'nasser' for 10 days with reference number 'RR-ABC123-1'.");

            EXPECT_DOES_NOT_CONTAINS(
                "Start date must be today (03/01/2024) or later.", true)
            EXPECT_DOES_NOT_CONTAINS("There is no car", true);

            break;

          case 9:  // Task_2_CreateRentalWithMixedCaseUserID
            RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;01/01/2024;03/01/2024;NaSSeR");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is now rented to "
                "'nasser' for 3 days with reference number 'RR-ABC123-1'.");
            EXPECT_DOES_NOT_CONTAINS("There is no car", true);

            break;

          case 10:  // Task_2_CreateRentalWithWeirdCasing
            RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
            RUN_COMMAND("CREATE_CAR aBc123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "Abc123;01/01/2024;01/02/2024;Nasser");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is now rented");
            EXPECT_DOES_NOT_CONTAINS("There is no car", true);
            EXPECT_DOES_NOT_CONTAINS("'Abc123'", false);
            break;

          case 11:  // Task_2_CreateInvalidRentalWithWeirdCasing
            RUN_COMMAND("CONFIGURE_DATE 01/01/2024");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "Abc123;01/01/2024;01/02/2024;Nasser");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "There is no car with the registration plate 'ABC123'.");
            EXPECT_DOES_NOT_CONTAINS(
                "Car with registration plate 'ABC123' is now rented", true);
            EXPECT_DOES_NOT_CONTAINS("'Abc123'", false);
            break;

          case 12:  // Task_2_CreateRentalCarAlreadyRentedOverStartDate
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;18/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;17/11/2024;21/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 5 days with reference");
            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is already rented at "
                "this "
                "time "
                "(RR-ABC123-1).");
            EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);
            break;

          case 13:  // Task_2_CreateRentalCarAlreadyRentedOverEndDate
            RUN_COMMAND("CONFIGURE_DATE 9/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;18/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2024;15/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 5 days with reference");
            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is already rented at "
                "this "
                "time "
                "(RR-ABC123-1).");
            EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);
            break;

          case 14:  // Task_2_CreateRentalCarAlreadyRentedEndDateOnStartDate
            RUN_COMMAND("CONFIGURE_DATE 1/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;18/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;9/11/2024;14/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 5 days with reference");
            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is already rented at "
                "this "
                "time "
                "(RR-ABC123-1).");
            EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);
            break;

          case 15:  // Task_2_CreateRentalCarAlreadyRentedStartDateOnEndDate
            RUN_COMMAND("CONFIGURE_DATE 1/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;18/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;18/11/2024;21/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 5 days with reference");
            EXPECT_CONTAINS(
                "Car with registration plate 'ABC123' is already rented at "
                "this "
                "time "
                "(RR-ABC123-1).");
            EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);
            break;

          case 16:  // Task_2_CreateRentalBeforeExistingRental
            RUN_COMMAND("CONFIGURE_DATE 1/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;18/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2024;13/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 5 days with reference");
            EXPECT_CONTAINS(
                "is now rented to 'luke' for 4 days with reference");
            EXPECT_CONTAINS("RR-ABC123-2");

            EXPECT_DOES_NOT_CONTAINS("is already rented at this", true);
            break;
          case 17:  // Task_2_CreateRentalCarAlreadyRentedSameDayFuture
            RUN_COMMAND("CONFIGURE_DATE 20/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;14/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;14/11/2024;Luke");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Start date must be today (20/11/2024) or later.");
            EXPECT_DOES_NOT_CONTAINS("is now rented to 'luke'", true);
            EXPECT_DOES_NOT_CONTAINS("RR-ABC123-2", true);
            break;

          case 18:  // Task_2_DisplayRentalsWithNoneAdded
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND("DISPLAY_RENTALS ABC123");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("No upcoming rentals");

            EXPECT_DOES_NOT_CONTAINS(
                "There is no car with the registration plate 'ABC123'.", true);
            break;

          case 19:  // Task_2_DisplayRentalsLowerCaseAccess
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR AbC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND("DISPLAY_RENTALS abc123");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("* 14/11/2024 - 16/11/2024 (3 days) - RR-ABC123-1");
            EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

            break;

          case 20:  // Task_2_DisplayRentalWhenDateWithinRentalDateRange
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR DEF123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "DEF123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "DEF123;14/12/2024;16/12/2024;Luke");
            RUN_COMMAND("CONFIGURE_DATE 15/11/2024");
            RUN_COMMAND("DISPLAY_RENTALS DEF123");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 3 days with reference number "
                "'RR-DEF123-1'");
            EXPECT_CONTAINS(
                "is now rented to 'luke' for 3 days with reference number "
                "'RR-DEF123-2'");
            EXPECT_CONTAINS("* 14/11/2024 - 16/11/2024 (3 days) - RR-DEF123-1");
            EXPECT_CONTAINS("* 14/12/2024 - 16/12/2024 (3 days) - RR-DEF123-2");
            EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

            EXPECT_DOES_NOT_CONTAINS("is already rented", true);

            break;

          case 21:  // Task_2_DisplayRentalWhenCurrentDateBetweenRentals;
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR DEF123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "DEF123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "DEF123;14/12/2024;16/12/2024;Luke");
            RUN_COMMAND("CONFIGURE_DATE 20/11/2024");
            RUN_COMMAND("DISPLAY_RENTALS DEF123");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "is now rented to 'nasser' for 3 days with reference number "
                "'RR-DEF123-1'");
            EXPECT_CONTAINS(
                "is now rented to 'luke' for 3 days with reference number "
                "'RR-DEF123-2'");

            EXPECT_CONTAINS("* 14/12/2024 - 16/12/2024 (3 days) - RR-DEF123-2");

            EXPECT_DOES_NOT_CONTAINS(
                "* 14/11/2024 - 16/11/2024 (3 days) - RR-DEF123-1", false);
            EXPECT_DOES_NOT_CONTAINS(" RR-DEF123-1", true);
            EXPECT_DOES_NOT_CONTAINS("No upcoming rentals", true);

            EXPECT_DOES_NOT_CONTAINS("is already rented", true);
            break;
          case 22:  // Task_2_DisplayCarNotAvailableToday
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 ToYota 200");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 15/11/2024");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("* 'ABC123' - Toyota, $200/day, not available");

            EXPECT_DOES_NOT_CONTAINS(", available", true);

            break;
          case 23:  // Task_2_DisplayCarNotAvailableTodayRentalStart
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 ToYota 200");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 14/11/2024");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("* 'ABC123' - Toyota, $200/day, not available");

            EXPECT_DOES_NOT_CONTAINS(", available", true);
            break;
          case 24:  // Task_2_DisplayCarNotAvailableTodayRentalEnd
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 ToYota 200");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2024;16/11/2024;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 16/11/2024");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("* 'ABC123' - Toyota, $200/day, not available");

            EXPECT_DOES_NOT_CONTAINS(", available", true);
            break;
          case 25:  // Task_2_DisplayMutipleCarsSomeAvailableToday
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND("CREATE_CAR DEF456 Honda 200");
            RUN_COMMAND("CREATE_CAR FED456 Honda 300");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;13/11/2024;20/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "DEF456;13/11/2024;15/11/2024;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "FED456;17/11/2024;21/11/2024;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 16/11/2024");
            RUN_COMMAND("DISPLAY_CARS");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("* 'ABC123' - Toyota, $100/day, not available");
            EXPECT_CONTAINS("* 'DEF456' - Honda, $200/day, available");
            EXPECT_CONTAINS("* 'FED456' - Honda, $300/day, available");
            break;

          default:
            cerr << "Test case not found: #" << test_number / 100 << "-"
                 << test_number % 100 << "\n\r";
            return TEST_RESULT_FAIL;
        }
        break;
      case 2:
        switch (test_number % 100) {
          case 1:  // Task_3_AddGpsUnitRentalOk
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");

            RUN_COMMAND("CONFIGURE_DATE 12/09/2025");
            RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("GPS Unit added to rental");
            EXPECT_DOES_NOT_CONTAINS("not added", true);

            break;
          case 2:  // Task_3_AddCarSeatNotFound
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");

            RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-2");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental reference 'RR-ABC123-2' not found, Child Seat not "
                "added.");
            EXPECT_DOES_NOT_CONTAINS("Child Seat added to rental", true);

            break;
          case 3:  // Task_3_AddCarSeatAlreadyStarted
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2025;16/11/2025;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 11/11/2025");
            RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental 'RR-ABC123-1' is in the past, too late to add Child "
                "Seat.");
            EXPECT_CONTAINS("RR-ABC123-2");

            EXPECT_DOES_NOT_CONTAINS("Child Seat added to rental", true);

            break;
          case 4:  // Task_3_AddInsuranceOk
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/12/2025;12/12/2025;mark");

            RUN_COMMAND("CONFIGURE_DATE 12/09/2025");
            RUN_COMMAND("ADD_INSURANCE RR-ABC123-2");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Insurance added to rental");
            EXPECT_CONTAINS("RR-ABC123-1");
            EXPECT_DOES_NOT_CONTAINS("not added", true);

            break;
          case 5:  // Task_3_AddInsuranceNotFound
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental reference 'RR-ABC123-1' not found, Insurance not "
                "added.");
            EXPECT_DOES_NOT_CONTAINS("Insurance added to rental", true);

            break;
          case 6:  // Task_3_AddInsuranceAlreadyStarted
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 11/11/2025");
            RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental 'RR-ABC123-1' is in the past, too late to add "
                "Insurance.");
            EXPECT_DOES_NOT_CONTAINS("Insurance added to rental", true);

            break;

          case 7:  // Task_3_DisplayReceiptRentalWithDiscountedCarCost
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;18/11/2025;Nasser");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Pickup Date: 10/11/2025");
            EXPECT_CONTAINS("Return Date: 18/11/2025");
            EXPECT_CONTAINS("Number of Days: 9");
            EXPECT_CONTAINS("Car Rental: $650");
            EXPECT_CONTAINS("GRAND TOTAL: $650");

            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                                     true);

            break;
          case 8:  // Task_3_DisplayReceiptRentalWithGpsUnitDiscounted
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;11/11/2025;20/11/2025;Nasser");
            RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Pickup Date: 11/11/2025");
            EXPECT_CONTAINS("Return Date: 20/11/2025");
            EXPECT_CONTAINS("Number of Days: 10");
            EXPECT_CONTAINS("Car Rental: $700");
            EXPECT_CONTAINS("GPS Unit Add-on: $25");
            EXPECT_CONTAINS("GRAND TOTAL: $725");

            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                                     true);

            break;

          case 9:  // Task_3_DisplayReceiptRentalWithInsuranceDiscounted
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
            break;
          case 10:  // Task_3_DisplayReceiptRentalNotCreated
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-2");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS(
                "Rental reference 'RR-ABC123-2' not found, no receipt to "
                "display.");

            EXPECT_DOES_NOT_CONTAINS("Booking Reference: RR-ABC123-2", true);
            EXPECT_DOES_NOT_CONTAINS("Pickup Date: 10/11/2025", true);
            EXPECT_DOES_NOT_CONTAINS("Return Date: 12/11/2025", true);
            EXPECT_DOES_NOT_CONTAINS("Number of Days: 3", true);

            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                                     true);

            break;
          case 11:  // Task_3_DisplayReceiptRentalInPast
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;12/11/2025;Nasser");
            RUN_COMMAND("CONFIGURE_DATE 04/12/2026");
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
          case 12:  // Task_3_DisplayReceiptRentalInFuture
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
          case 13:  // Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsuranceDifferentRentals
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;10/11/2025;11/11/2025;Nasser");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;14/11/2025;16/11/2025;Luke");
            RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
            RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
            RUN_COMMAND("ADD_INSURANCE RR-ABC123-2");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-2");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Pickup Date: 10/11/2025");
            EXPECT_CONTAINS("Return Date: 11/11/2025");
            EXPECT_CONTAINS("Number of Days: 2");
            EXPECT_CONTAINS("Car Rental: $200");
            EXPECT_CONTAINS("GPS Unit Add-on: $10");
            EXPECT_CONTAINS("Child Seat Add-on: $4");

            EXPECT_CONTAINS("GRAND TOTAL: $214");

            EXPECT_CONTAINS("Pickup Date: 14/11/2025");
            EXPECT_CONTAINS("Return Date: 16/11/2025");
            EXPECT_CONTAINS("Number of Days: 3");
            EXPECT_CONTAINS("Car Rental: $300");
            EXPECT_CONTAINS("Insurance Add-on: $15");

            EXPECT_CONTAINS("GRAND TOTAL: $315");

            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                                     true);
            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-2 not found",
                                     true);
            EXPECT_DOES_NOT_CONTAINS("Insurance Add-on: $10", true);
            EXPECT_DOES_NOT_CONTAINS("GPS Unit Add-on: $15", true);
            EXPECT_DOES_NOT_CONTAINS("Child Seat Add-on: $6", true);
            break;
          case 14:  // Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsuranceDiscountApplied
            RUN_COMMAND("CONFIGURE_DATE 12/11/2024");
            RUN_COMMAND("CREATE_CAR ABC123 Toyota 100");
            RUN_COMMAND_WITH_OPTIONS("CREATE_RENTAL",
                                     "ABC123;11/11/2025;20/11/2025;Nasser");
            RUN_COMMAND("ADD_GPS_UNIT RR-ABC123-1");
            RUN_COMMAND("ADD_CHILD_SEAT RR-ABC123-1");
            RUN_COMMAND("ADD_INSURANCE RR-ABC123-1");
            RUN_COMMAND("DISPLAY_RECEIPT RR-ABC123-1");
            RUN_COMMAND("EXIT");

            EXPECT_CONTAINS("Pickup Date: 11/11/2025");
            EXPECT_CONTAINS("Return Date: 20/11/2025");
            EXPECT_CONTAINS("Number of Days: 10");
            EXPECT_CONTAINS("Car Rental: $700");
            EXPECT_CONTAINS("GPS Unit Add-on: $25");
            EXPECT_CONTAINS("Child Seat Add-on: $10");
            EXPECT_CONTAINS("Insurance Add-on: $35");
            EXPECT_CONTAINS("GRAND TOTAL: $770");

            EXPECT_DOES_NOT_CONTAINS("Rental reference 'RR-ABC123-1' not found",
                                     true);
            break;
          default:
            cerr << "Test case not found: #" << test_number / 100 << "-"
                 << test_number % 100 << "\n\r";
            return TEST_RESULT_FAIL;
        }
        break;
      default:
        cerr << "Test case not found: #" << test_number << "\n\r";
        return TEST_RESULT_FAIL;
    }
  }
  cerr << "PASSED Test " << test_number << "." << "\n\r" << "\n\r"
       << "--------------------------------------------------------------------"
          "--------"
       << "\n\r" << "\n\r";
  return TEST_RESULT_PASS;
}

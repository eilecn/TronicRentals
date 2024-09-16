option(TASK_1_TEST_CASES "Run the test cases for Task 1" ON)   # 20 tests
option(TASK_2_TEST_CASES "Run the test cases for Task 2" ON)  # 50 tests
option(TASK_3_TEST_CASES "Run the test cases for Task 3" ON)  # 30 tests

# Add the test executable and link it with the library targets
add_executable(tester_app ./tester.cpp)

# Include the "src" directory to access the source files
target_include_directories(tester_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Link the subdirectory targets to the test executable
target_link_libraries(tester_app SrcTarget SrcAppSupportTarget)

# Add the tests to CTest for Task 1
if(TASK_1_TEST_CASES)
  add_test(NAME Task_1_ZeroCars COMMAND tester_app 1)
  add_test(NAME Task_1_CreateNewCar COMMAND tester_app 2)
  add_test(NAME Task_1_CreateNewCarWithDisplay COMMAND tester_app 3)
  add_test(NAME Task_1_CreateMultipleCarsWithDisplay COMMAND tester_app 5)
  add_test(NAME Task_1_CreateCarWithInvalidRegistrationPlateLength COMMAND tester_app 6)
  add_test(NAME Task_1_CreateCarWithInvalidRegistrationPlateAllLetters COMMAND tester_app 8)
  add_test(NAME Task_1_CreateCarWithRegistrationPlateLowerCase COMMAND tester_app 11)
  add_test(NAME Task_1_CreateCarRentalFeeZero COMMAND tester_app 13)
  add_test(NAME Task_1_CreateCarWithDuplicateMake COMMAND tester_app 17)
  add_test(NAME Task_1_CreateCarWithDuplicateRentalFee COMMAND tester_app 18)
endif()

# Add the tests to CTest for Task 2
if(TASK_2_TEST_CASES)
  add_test(NAME Task_2_DisplayDateNotConfigured COMMAND tester_app 21)
  add_test(NAME Task_2_ConfigureDateWithoutDisplay COMMAND tester_app 22)
  add_test(NAME Task_2_ConfigureDate COMMAND tester_app 23)
  add_test(NAME Task_2_ConfigureWeirdDate COMMAND tester_app 24)
  add_test(NAME Task_2_ReconfigureDateInvalidYesterday COMMAND tester_app 27)
  add_test(NAME Task_2_ReconfigureDateInvalidLastMonth COMMAND tester_app 28)
  add_test(NAME Task_2_CreateRentalNoCars COMMAND tester_app 32)
  add_test(NAME Task_2_CreateRentalSimple COMMAND tester_app 34)
  add_test(NAME Task_2_CreateRentalSimpleWithDaysCalculated COMMAND tester_app 37)
  add_test(NAME Task_2_CreateRentalSimpleWithReferenceNumber COMMAND tester_app 38)
  add_test(NAME Task_2_CreateRentalSimpleCompleteMessage COMMAND tester_app 39)
  add_test(NAME Task_2_CreateRentalSimpleCompleteMessageFutureDateNextMonth COMMAND tester_app 41)
  add_test(NAME Task_2_CreateRentalEndDateBeforeStartDate COMMAND tester_app 44)
  add_test(NAME Task_2_CreateRentalCarAlreadyRentedSameDayFuture COMMAND tester_app 46)
  add_test(NAME Task_2_CreateRentalCarAlreadyRentedSameDateRange COMMAND tester_app 47)
  add_test(NAME Task_2_CreateRentalSameCarDifferentDates COMMAND tester_app 52)
  add_test(NAME Task_2_DisplayRentalsNotConfigured COMMAND tester_app 54)
  add_test(NAME Task_2_DisplayRentalsSingleRental COMMAND tester_app 57)
  add_test(NAME Task_2_DisplayRentalsSingleRentalDifferentCarDisplayRented COMMAND tester_app 58)
  add_test(NAME Task_2_DisplayRentalsMultipleRentalsDifferentCars COMMAND tester_app 60)
  add_test(NAME Task_2_DisplayRentalAfterSystemDateChange COMMAND tester_app 62)
  add_test(NAME Task_2_DisplayRentalsMultipleRentalsSameCarDifferentDatesAfterSystemDateChange COMMAND tester_app 63)
  add_test(NAME Task_2_DisplayRentalsMultipleRentalsDifferentCarsAfterSystemDateChangeFarInFuture COMMAND tester_app 65)
  add_test(NAME Task_2_Display_Car_Available_Today COMMAND tester_app 66)
  add_test(NAME Task_2_Display_Cars_All_Not_Available_Today COMMAND tester_app 69)
endif()

# Add the tests to CTest for Task 3
if(TASK_3_TEST_CASES)
  add_test(NAME Task_3_AddGpsUnitRentalNotFound COMMAND tester_app 71)
  add_test(NAME Task_3_AddGpsUnitRentalAlreadyStarted COMMAND tester_app 72)
  add_test(NAME Task_3_AddCarSeatOk COMMAND tester_app 73)
  add_test(NAME Task_3_DisplayReceiptRentalNotFound COMMAND tester_app 76)
  add_test(NAME Task_3_DisplayReceiptRental COMMAND tester_app 78)
  add_test(NAME Task_3_DisplayReceiptRentalWithCarCost COMMAND tester_app 79)
  add_test(NAME Task_3_DisplayReceiptRentalWithGpsUnit COMMAND tester_app 81)
  add_test(NAME Task_3_DisplayReceiptRentalWithCarSeatDiscounted COMMAND tester_app 84)
  add_test(NAME Task_3_DisplayReceiptRentalWithCarSeatDifferentRentals COMMAND tester_app 85)
  add_test(NAME Task_3_DisplayReceiptRentalWithInsurance COMMAND tester_app 86)
  add_test(NAME Task_3_DisplayReceiptRentalWithInsuranceDiscountedCarCost COMMAND tester_app 87)
  add_test(NAME Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsurance COMMAND tester_app 89)
  add_test(NAME Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsuranceDifferentRentals COMMAND tester_app 91)
  add_test(NAME Task_3_AddCarSeatDifferentRentals COMMAND tester_app 94)
  add_test(NAME Task_3_DisplayReceiptRentalActive COMMAND tester_app 98)
endif()

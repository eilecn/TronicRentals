option(ENABLE_STUDENT_TEST "Run the student created test cases" ON)   # 50 tests

# Add the test executable and link it with the library targets
add_executable(student_tester_app ./student_tester.cpp)

# Include the "src" directory to access the source files
target_include_directories(student_tester_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Link the subdirectory targets to the test executable
target_link_libraries(student_tester_app SrcTarget SrcAppSupportTarget)

# Create car with lowercase make and just general make checks
# Create car with duplicate number plate

# Recogiqure date invalid last year
if (ENABLE_STUDENT_TEST)
  add_test(NAME Tests_Student________________________ COMMAND student_tester_app 0)

  if (TASK_1_TEST_CASES)
    add_test(NAME Task_1_CreateMultipleNewCars COMMAND student_tester_app 1)
    add_test(NAME Task_1_CreateCarWithInvalidRegistrationPlateAllNumbers COMMAND student_tester_app 2)
    add_test(NAME Task_1_CreateCarWithInvalidRegistrationPlateToShort COMMAND student_tester_app 3)
    add_test(NAME Task_1_CreateInvalidCarWithLowercaseNumberPlate COMMAND student_tester_app 4)
    add_test(NAME Task_1_CreateCarWithInvalidRentalFeeNotNumeric COMMAND student_tester_app 5)
    add_test(NAME Task_1_CreateCarWithInvalidRentalFeeNotPositive COMMAND student_tester_app 6)
    add_test(NAME Task_1_CreateCarWithLowerCaseMake COMMAND student_tester_app 7)
    add_test(NAME Task_1_DisplayCarsWithLowerCaseRegistrationPlate COMMAND student_tester_app 8)
    add_test(NAME Task_1_CreateCarWithDuplicateRegistrationPlate COMMAND student_tester_app 11)

  endif()

  if (TASK_2_TEST_CASES)
    add_test(NAME Task_2_ConfigureDateSameDayAsCurrentDate COMMAND student_tester_app 101)
    add_test(NAME Task_2_ConfigureDateInvalidLastYear COMMAND student_tester_app 102)
    add_test(NAME Task_2_CreateRentalDateNotConfigured COMMAND student_tester_app 106)
    add_test(NAME Task_2_CreateRentalStartsInPast COMMAND student_tester_app 107)
    add_test(NAME Task_2_CreateRentalStartsOnSystemTime COMMAND student_tester_app 108)
    add_test(NAME Task_2_CreateRentalWithMixedCaseUserID COMMAND student_tester_app 109)
    add_test(NAME Task_2_CreateRentalWithWeirdCasing COMMAND student_tester_app 110)
    add_test(NAME Task_2_CreateInvalidRentalWithWeirdCasing COMMAND student_tester_app 111)
    add_test(NAME Task_2_CreateRentalCarAlreadyRentedOverStartDate COMMAND student_tester_app 112)
    add_test(NAME Task_2_CreateRentalCarAlreadyRentedOverEndDate COMMAND student_tester_app 113)
    add_test(NAME Task_2_CreateRentalCarAlreadyRentedEndDateOnStartDate COMMAND student_tester_app 114)
    add_test(NAME Task_2_CreateRentalCarAlreadyRentedStartDateOnEndDate COMMAND student_tester_app 115)
    add_test(NAME Task_2_CreateRentalBeforeExistingRental COMMAND student_tester_app 116)
    add_test(NAME Task_2_CreateRentalCarAlreadyRentedSameDayPast COMMAND student_tester_app 117)
    add_test(NAME Task_2_DisplayRentalsWithNoneAdded COMMAND student_tester_app 118)
    add_test(NAME Task_2_DisplayRentalsLowerCaseAccess COMMAND student_tester_app 119)
    add_test(NAME Task_2_DisplayRentalWhenDateWithinRentalDateRange COMMAND student_tester_app 120)
    add_test(NAME Task_2_DisplayRentalWhenCurrentDateBetweenRentals COMMAND student_tester_app 121)
    add_test(NAME Task_2_DisplayCarNotAvailableToday COMMAND student_tester_app 122)
    add_test(NAME Task_2_DisplayCarNotAvailableTodayRentalStart COMMAND student_tester_app 123)
    add_test(NAME Task_2_DisplayCarNotAvailableTodayRentalEnd COMMAND student_tester_app 124)
    add_test(NAME Task_2_DisplayMutipleCarsSomeAvailableToday COMMAND student_tester_app 125)
    
    # add_test(NAME COMMAND student_tester_app 12)
    # add_test(NAME COMMAND student_tester_app 12)
    # add_test(NAME COMMAND student_tester_app 12)
    # add_test(NAME COMMAND student_tester_app 12)
    

  endif()

  if (TASK_3_TEST_CASES)
    add_test(NAME Task_3_AddGpsUnitRentalOk COMMAND student_tester_app 201)
    add_test(NAME Task_3_AddCarSeatNotFound COMMAND student_tester_app 202)
    add_test(NAME Task_3_AddCarSeatAlreadyStarted COMMAND student_tester_app 203)
    add_test(NAME Task_3_AddInsuranceOk COMMAND student_tester_app 204)
    add_test(NAME Task_3_AddInsuranceNotFound COMMAND student_tester_app 205)
    add_test(NAME Task_3_AddInsuranceAlreadyStarted COMMAND student_tester_app 206)
    add_test(NAME Task_3_DisplayReceiptRentalWithDiscountedCarCost COMMAND student_tester_app 207)
    add_test(NAME Task_3_DisplayReceiptRentalWithGpsUnitDiscounted COMMAND student_tester_app 208)
    add_test(NAME Task_3_DisplayReceiptRentalWithInsuranceDiscounted COMMAND student_tester_app 209)
    add_test(NAME Task_3_DisplayReceiptRentalNotCreated COMMAND student_tester_app 210)
    add_test(NAME Task_3_DisplayReceiptRentalInPast COMMAND student_tester_app 211)
    add_test(NAME Task_3_DisplayReceiptRentalInFuture COMMAND student_tester_app 212)
    add_test(NAME Task_3_DisplayReceiptRentalWithAllAddOnsDifferentRentals COMMAND student_tester_app 213)
    add_test(NAME Task_3_DisplayReceiptRentalWithGpsUnitCarSeatInsuranceDiscountApplied COMMAND student_tester_app 214)
    # add_test(NAME COMMAND student_tester_app 21)
    # add_test(NAME COMMAND student_tester_app 21)
    # add_test(NAME COMMAND student_tester_app 21)
    # add_test(NAME COMMAND student_tester_app 21)
    # add_test(NAME COMMAND student_tester_app 21)
  endif()
endif()
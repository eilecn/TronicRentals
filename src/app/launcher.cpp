

#include "launcher.h"

#include <iostream>

#include "message.h"
#include "utils.h"

using namespace std;

/*
**********************************************************************************
  DO NOT MODIFY THIS FILE.
  During marking, we will use the original version of this file that we
    provided. If you change the file, the automated tests will fail and you will
    most likely lose marks.
**********************************************************************************
*/

string Launcher::COMMAND_PREFIX = "tronicrentals> ";

Launcher::Launcher() {}

bool Launcher::ProcessCommand(const std::string &cmd_input) {
  return ProcessCommand(cmd_input, {});
}

bool Launcher::ProcessCommand(const std::string &cmd_input,
                              std::vector<std::string> options) {
  // Check it is a valid command name
  string cmd_input_name = Utils::GetFirstWord(cmd_input);
  Command command = Command::Find(cmd_input_name);
  if (command == Command::INVALID) {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input_name});
    return true;
  }

  // Check the number of arguments provided match as the command expects
  vector<string> args = Utils::SplitString(cmd_input);
  int num_args_provided = args.size() - 1;
  int num_args_expected = command.GetNumArgs();
  if (num_args_provided != num_args_expected) {
    string provided = to_string(num_args_provided) + " argument" +
                      (num_args_provided == 1 ? "" : "s");
    string expected = to_string(num_args_expected) + " argument" +
                      (num_args_expected == 1 ? "" : "s");
    cout << Message::WRONG_ARGUMENT_COUNT.GetMessage(
                {command.GetName(), provided, expected})
         << endl;
    return true;
  }

  std::vector<std::string> options_for_app;
  if (command.HasOptions()) {
    if (options.size() == 0) {
      // prompt the user for the options, as none were provided
      for (int i = 0; i < command.GetNumOptions(); i++) {
        cout << "  " << command.GetOptionPrompt(i) << ": ";
        string option;
        std::getline(std::cin, option);
        option = Utils::TrimString(option);
        options_for_app.push_back(option);
      }
    } else if (options.size() == command.GetNumOptions()) {
      // if the options are provided here (e.g. from the test case), use them
      options_for_app = options;
      // simulate the user input for the options
      for (int i = 0; i < command.GetNumOptions(); i++) {
        cout << "  " << command.GetOptionPrompt(i) << ": " << options_for_app[i]
             << endl;
      }
    } else {
      // incorrect number of options are provided, error message
      string expected = to_string(command.GetNumOptions()) + " option" +
                        (command.GetNumOptions() == 1 ? "" : "s");
      string provided = to_string(options.size()) + " option" +
                        (options.size() == 1 ? "" : "s");
      cout << Message::WRONG_OPTION_COUNT.GetMessage(
                  {command.GetName(), provided, expected})
           << endl;
      return true;
    }
  }

  if (command == Command::CREATE_CAR) {
    app_.CreateCar(args[1], args[2], args[3]);
  } else if (command == Command::DISPLAY_CARS) {
    app_.DisplayCars();
  } else if (command == Command::CONFIGURE_DATE) {
    app_.ConfigureDate(args[1]);
  } else if (command == Command::DISPLAY_DATE) {
    app_.DisplayDate();
  } else if (command == Command::CREATE_RENTAL) {
    app_.CreateRental(options_for_app);
  } else if (command == Command::DISPLAY_RENTALS) {
    app_.DisplayRentals(args[1]);
  } else if (command == Command::ADD_GPS_UNIT) {
    app_.AddGPSUnit(args[1]);
  } else if (command == Command::ADD_CHILD_SEAT) {
    app_.AddChildSeat(args[1]);
  } else if (command == Command::ADD_INSURANCE) {
    app_.AddInsurance(args[1]);
  } else if (command == Command::DISPLAY_RECEIPT) {
    app_.DisplayReceipt(args[1]);
  } else if (command == Command::HELP) {
    cout << Command::GetHelp() << endl;
  } else if (command == Command::EXIT) {
    Message::END.PrintMessage();
    return false;
  } else {
    Message::COMMAND_NOT_FOUND.PrintMessage({cmd_input});
  }
  return true;
}

void Launcher::Start() {
  PrintBanner();
  cout << Command::GetHelp() << endl;

  // Keep reading commands until the user exits
  string cmd_input;
  do {
    cout << COMMAND_PREFIX;
    std::getline(std::cin, cmd_input);
    cmd_input = Utils::TrimString(cmd_input);
  } while (ProcessCommand(cmd_input));
}

void Launcher::PrintBanner() const {
  // https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
  // https://www.freeformatter.com/java-dotnet-escape.html#before-output

  std::string banner =
      "\r\n  _____                             _              ___              "
      "       _                _            \r\n"
      " |_   _|    _ _    ___    _ _      (_)     __     | _ \\    ___    _ _  "
      " "
      "  | |_    __ _     | |     ___   \r\n"
      "   | |     | '_|  / _ \\  | ' \\     | |    / _|    |   /   / -_)  | ' "
      "\\    |  _|  / _` |    | |    (_-<   \r\n"
      "  _|_|_   _|_|_   \\___/  |_||_|   _|_|_   \\__|_   |_|_\\   \\___|  "
      "|_||_|   _\\__|  \\__,_|   _|_|_   /__/_  \r\n"
      "_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|"
      "\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|"
      "\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| \r\n"
      "\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'"
      "\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-' \r\n";

  cout << banner << endl;
}

std::string Launcher::GetCommandPrefix() const { return COMMAND_PREFIX; }

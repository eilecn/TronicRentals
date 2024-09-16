#include "command.h"

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

// Task 1 commands
const Command Command::CREATE_CAR(
    "CREATE_CAR", 3,
    "Create a new car with the specified <REGISTRATION_PLATE>, <MAKE> and "
    "<DAILY_RENTAL_FEE>");
const Command Command::DISPLAY_CARS("DISPLAY_CARS", 0,
                                    "Display all cars in the system");

// Task 2 commands
const Command Command::CONFIGURE_DATE("CONFIGURE_DATE", 1,
                                      "Configure the system date to <DATE>");
const Command Command::DISPLAY_DATE("DISPLAY_DATE", 0,
                                    "Display the current system date");
const Command Command::CREATE_RENTAL("CREATE_RENTAL", 0, "Create a new rental",
                                     {"Registration Plate",
                                      "Start date (DD/MM/YYYY)",
                                      "End date (DD/MM/YYYY)", "Customer ID"});
const Command Command::DISPLAY_RENTALS(
    "DISPLAY_RENTALS", 1,
    "Display all rentals for the specified <REGISTRATION_PLATE>");

// Task 3 commands
const Command Command::ADD_GPS_UNIT(
    "ADD_GPS_UNIT", 1, "Add a GPS Unit to the specified <RENTAL_REFERENCE>");

const Command Command::ADD_CHILD_SEAT("ADD_CHILD_SEAT", 1,
                                      "Add a Child Seat to the specified "
                                      "<RENTAL_REFERENCE>");

const Command Command::ADD_INSURANCE("ADD_INSURANCE", 1,
                                     "Add insurance to the specified "
                                     "<RENTAL_REFERENCE>");

const Command Command::DISPLAY_RECEIPT("DISPLAY_RECEIPT", 1,
                                       "Display the receipt for the specified "
                                       "<RENTAL_REFERENCE>");

// General system commands
const Command Command::HELP("HELP", 0, "Print usage");
const Command Command::EXIT("EXIT", 0, "Exit the application");
const Command Command::INVALID("_____INVALID____", 0,
                               "Placeholder for INVALID Command value");

std::initializer_list<Command> Command::commands = {
    Command::CREATE_CAR,      Command::DISPLAY_CARS,   Command::CONFIGURE_DATE,
    Command::DISPLAY_DATE,    Command::CREATE_RENTAL,  Command::DISPLAY_RENTALS,
    Command::ADD_GPS_UNIT,    Command::ADD_CHILD_SEAT, Command::ADD_INSURANCE,
    Command::DISPLAY_RECEIPT, Command::HELP,           Command::EXIT};

Command::Command(const std::string &name, int num_args,
                 const std::string &message) {
  this->name_ = name;
  this->num_args_ = num_args;
  this->message_ = message;
}

Command::Command(const std::string &name, int num_args,
                 const std::string &message,
                 const std::vector<std::string> &option_prompts) {
  this->name_ = name;
  this->num_args_ = num_args;
  this->message_ = message;
  this->option_prompts_ = option_prompts;
}

std::string Command::GetName() const { return name_; }

bool Command::HasArguments() const { return num_args_ > 0; }

int Command::GetNumArgs() const { return num_args_; }

bool Command::HasOptions() const { return option_prompts_.size() > 0; }

int Command::GetNumOptions() const { return option_prompts_.size(); }

std::string Command::GetMessage() const { return message_; }

std::string Command::GetOptionPrompt(int index) const {
  return option_prompts_[index];
}

bool Command::operator==(const Command &other) const {
  return name_ == other.name_;
}

bool Command::operator!=(const Command &other) const {
  return !(*this == other);
}

std::string Command::GetHelp() {
  std::string help;
  for (const Command &command : commands) {
    int num_args = command.GetNumArgs();
    std::string command_name = command.GetName();
    help += command_name + "\t";
    if (command_name.length() < 8) {
      help += "\t";
    }
    help += "[" + (num_args == 0 ? "no" : to_string(command.GetNumArgs())) +
            " argument" + (num_args == 1 ? "" : "s") + "]";
    help += "\t";
    help += command.GetMessage() + "\n";
  }
  return help;
}
// ====== UNTIL HERE

bool Command::IsValidCommand(const std::string &cmd_input) {
  return Find(cmd_input) != Command::INVALID;
}

const Command &Command::Find(const std::string &cmd_input) {
  string cmd = Utils::GetFirstWord(cmd_input);
  cmd = Utils::GetUppercaseUnderscore(cmd);

  for (const Command &command : commands) {
    if (command.GetName() == cmd) {
      return command;
    }
  }

  return Command::INVALID;
}

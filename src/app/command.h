#if !defined(COMMAND_HPP)
#define COMMAND_HPP

#include <initializer_list>
#include <string>
#include <vector>

/*
**********************************************************************************
  DO NOT MODIFY THIS FILE.
  During marking, we will use the original version of this file that we
    provided. If you change the file, the automated tests will fail and you will
    most likely lose marks.
**********************************************************************************
*/

class Command {
 private:
  std::string name_;
  int num_args_;
  std::string message_;
  std::vector<std::string> option_prompts_;

  static std::initializer_list<Command> commands;

 public:
  static const Command CREATE_CAR;
  static const Command DISPLAY_CARS;
  static const Command CONFIGURE_DATE;
  static const Command DISPLAY_DATE;
  static const Command CREATE_RENTAL;
  static const Command DISPLAY_RENTALS;
  static const Command ADD_GPS_UNIT;
  static const Command ADD_CHILD_SEAT;
  static const Command ADD_INSURANCE;
  static const Command DISPLAY_RECEIPT;
  static const Command HELP;
  static const Command EXIT;
  static const Command INVALID;

  Command(const std::string &name, int num_args, const std::string &message);
  Command(const std::string &name, int num_args, const std::string &message,
          const std::vector<std::string> &option_prompts);

  std::string GetName() const;
  bool HasArguments() const;
  int GetNumArgs() const;
  bool HasOptions() const;
  int GetNumOptions() const;
  std::string GetMessage() const;
  std::string GetOptionPrompt(int index) const;

  bool operator==(const Command &other) const;
  bool operator!=(const Command &other) const;

  static std::string GetHelp();
  static bool IsValidCommand(const std::string &cmd_input);
  static const Command &Find(const std::string &cmd_input);
};

#endif  // COMMAND_HPP

#if !defined(LAUNCHER_H)
#define LAUNCHER_H

#include <initializer_list>
#include <string>
#include <vector>

#include "app.h"
#include "command.h"

/*
**********************************************************************************
  DO NOT MODIFY THIS FILE.
  During marking, we will use the original version of this file that we
    provided. If you change the file, the automated tests will fail and you will
    most likely lose marks.
**********************************************************************************
*/

class Launcher {
 private:
  App app_;
  static std::string COMMAND_PREFIX;

 public:
  Launcher();
  void Start();
  bool ProcessCommand(const std::string &cmd);
  bool ProcessCommand(const std::string &cmd, std::vector<std::string> options);
  void PrintBanner() const;
  std::string GetCommandPrefix() const;
};

#endif  // LAUNCHER_H

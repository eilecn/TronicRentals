#if !defined(UTILS_H)
#define UTILS_H

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

class Utils {
 private:
  static std::string WHITESPACE;

 public:
  static std::string TrimString(const std::string &str);
  static std::string TrimStringLeft(const std::string &str);
  static std::string TrimStringRight(const std::string &str);
  static std::string GetFirstWord(const std::string &str);
  static std::string GetUppercaseUnderscore(const std::string &str);
  static std::string GetUppercase(const std::string &str);
  static std::string GetLowercase(const std::string &str);
  static std::vector<std::string> SplitString(const std::string &str);
  static std::vector<std::string> SplitString(const std::string &str,
                                              const std::string &delim);
  static bool StartsWith(const std::string &str, const std::string &prefix);
  static bool StartsWithIgnoreCase(const std::string &str,
                                   const std::string &prefix);
  static bool Contains(const std::string &str, const std::string &s,
                       bool ignore_case);
  static bool IsInteger(const std::string &str);
};

#endif  // UTILS_H

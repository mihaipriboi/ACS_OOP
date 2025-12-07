#ifndef PASSWORD_UTILS_H
#define PASSWORD_UTILS_H

#include <string>
#include "../exceptions/exceptions.h"

using namespace std;

class PasswordUtils {
public:
  PasswordUtils() {}

  // Evaluates password strength: "weak", "ok", "good"
  string evaluateStrength(const string& password) const;

  // Throws WeakPasswordException if password is weak
  void ensureStrongEnough(const string& password) const;

  // Validates email format, throws EmailFormatException if invalid
  void validateEmail(const string& email) const;

private:
  bool hasUpper(const string& s) const;
  bool hasLower(const string& s) const;
  bool hasDigit(const string& s) const;
  bool hasSpecial(const string& s) const;
};
#endif

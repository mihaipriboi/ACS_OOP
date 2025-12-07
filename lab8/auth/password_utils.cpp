#include "password_utils.h"
#include <cctype>

string PasswordUtils::evaluateStrength(const string& password) const {
  int score = 0;

  if (password.length() >= 8) score++;
  if (hasUpper(password)) score++;
  if (hasLower(password)) score++;
  if (hasDigit(password)) score++;
  if (hasSpecial(password)) score++;

  if (score <= 2) return "weak";
  if (score == 3 || score == 4) return "ok";
  return "good";
}

void PasswordUtils::ensureStrongEnough(const string& password) const {
  string strength = evaluateStrength(password);
  if (strength == "weak") {
    throw WeakPasswordException("Password is too weak");
  }
}

void PasswordUtils::validateEmail(const string& email) const {
  size_t atPos = email.find('@');
  size_t dotPos = email.find('.', atPos);
  if (atPos == string::npos || dotPos == string::npos || atPos == 0 || dotPos == email.length() - 1) {
    throw EmailFormatException(email);
  }
}

bool PasswordUtils::hasUpper(const string& s) const {
  for (char c : s) if (isupper(c)) return true;
  return false;
}

bool PasswordUtils::hasLower(const string& s) const {
  for (char c : s) if (islower(c)) return true;
  return false;
}

bool PasswordUtils::hasDigit(const string& s) const {
  for (char c : s) if (isdigit(c)) return true;
  return false;
}

bool PasswordUtils::hasSpecial(const string& s) const {
  for (char c : s) if (!isalnum(c)) return true;
  return false;
}

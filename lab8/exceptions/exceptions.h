#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class LoginFailedException : public runtime_error {
public:
  explicit LoginFailedException(const string& msg)
    : runtime_error("Login failed: " + msg) {}
};

class InvalidTripDataException : public runtime_error {
public:
  explicit InvalidTripDataException(const string& msg)
    : runtime_error("Invalid trip data: " + msg) {}
};

class InvalidCityException : public runtime_error {
public:
  explicit InvalidCityException(const string& msg)
    : runtime_error("Invalid city name: " + msg) {}
};

class WeakPasswordException : public runtime_error {
public:
  explicit WeakPasswordException(const string& msg)
    : runtime_error("Weak password: " + msg) {}
};

class EmailFormatException : public runtime_error {
public:
  explicit EmailFormatException(const string& msg)
    : runtime_error("Invalid email format: " + msg) {}
};

class RegistrationException : public runtime_error {
public:
  explicit RegistrationException(const string& msg)
    : runtime_error("Registration error: " + msg) {}
};

class TripNotFoundException : public runtime_error {
public:
  explicit TripNotFoundException(const string& msg)
    : runtime_error("Trip not found: " + msg) {}
};

class ReservationException : public runtime_error {
public:
  explicit ReservationException(const string& msg)
    : runtime_error("Reservation error: " + msg) {}
};

#endif

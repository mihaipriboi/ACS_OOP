#pragma once

#include <exception>
#include <string>

using namespace std;

class MapException : public exception {
protected:
  string message;
public:
  MapException(const string& msg) : message(msg) {}
  const char* what() const noexcept override { return message.c_str(); }
};

class FileMissingException : public MapException {
public:
  FileMissingException(const string& filename) : MapException("File not found: " + filename) {}
};

class MapParseException : public MapException {
public:
  MapParseException(const string& detail) : MapException("Parse Error: " + detail) {}
};

class MapValidationException : public MapException {
public:
  MapValidationException(const string& detail) : MapException("Validation Error: " + detail) {}
};
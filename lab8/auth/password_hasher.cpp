#include "password_hasher.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

PasswordHasher::PasswordHasher() {
  srand((unsigned int)time(nullptr));
}

string PasswordHasher::generateKey(int length) {
  const char hexChars[] = "0123456789abcdef";
  string key;
  for (int i = 0; i < length; i++) {
    key += hexChars[rand() % 16];
  }
  return key;
}

string PasswordHasher::bytesToHex(const vector<unsigned char>& data) {
  stringstream ss;
  ss << hex << setfill('0');
  for (auto c : data) {
    ss << setw(2) << (int)c;
  }
  return ss.str();
}

string PasswordHasher::hashPassword(const string& key, const string& password) {
  // HMAC-like simplificat: SHA256(key + password)
  string combined = key + password;
  vector<unsigned char> digest = sha.compute(combined);
  return bytesToHex(digest);
}

bool PasswordHasher::verifyPassword(const string& key, const string& password, const string& storedHash) {
  string hashAttempt = hashPassword(key, password);
  return hashAttempt == storedHash;
}

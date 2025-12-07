#ifndef PASSWORD_HASHER_H
#define PASSWORD_HASHER_H

#include <string>
#include <vector>
#include "../crypto/sha256_simple.h"

using namespace std;

class PasswordHasher {
public:
  PasswordHasher();
  
  // Generate a random key (hex string)
  string generateKey(int length = 16);

  // Create hash from key + password (HMAC-like)
  string hashPassword(const string& key, const string& password);

  // Verify password by recomputing hash with stored key
  bool verifyPassword(const string& key, const string& password, const string& storedHash);

private:
  SHA256 sha;
  string bytesToHex(const vector<unsigned char>& data);
};

#endif

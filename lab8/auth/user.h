#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
  User();
  User(const string& username, const string& email, const string& key, const string& hash);

  string getUsername() const;
  string getEmail() const;
  string getKey() const;
  string getPasswordHash() const;

  void setUsername(const string& username);
  void setEmail(const string& email);

private:
  string username;
  string email;
  string key;          // HMAC-like key
  string passwordHash; // SHA256(key+password)
};

#endif

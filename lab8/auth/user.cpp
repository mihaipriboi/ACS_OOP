#include "user.h"

User::User() {}

User::User(const string& username, const string& email, const string& key, const string& hash)
  : username(username), email(email), key(key), passwordHash(hash) {}

string User::getUsername() const { return username; }
string User::getEmail() const { return email; }
string User::getKey() const { return key; }
string User::getPasswordHash() const { return passwordHash; }

void User::setUsername(const string& u) { username = u; }
void User::setEmail(const string& e) { email = e; }

#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <string>
#include <vector>
#include "user.h"
#include "password_hasher.h"
#include "password_utils.h"
#include "../exceptions/exceptions.h"

using namespace std;

class AuthManager {
public:
  AuthManager(const string& usersCsvFile);

  // Creare cont nou; arunca exceptii daca email/parola invalida
  void registerUser(const string& username, const string& email, const string& password);

  // Login utilizator/operator; returneaza pointer la User sau arunca exceptie
  User* login(const string& email, const string& password);

  // Incarca utilizatori din CSV
  void loadUsers();

  // Salveaza utilizatori in CSV
  void saveUsers();

private:
  string usersCsvFile;
  vector<User> users;

  PasswordHasher hasher;
  PasswordUtils utils;

  User* findUserByEmail(const string& email);
};
#endif

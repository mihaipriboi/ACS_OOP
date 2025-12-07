#include "auth_manager.h"
#include <fstream>
#include <sstream>

AuthManager::AuthManager(const string& file) : usersCsvFile(file) {
  loadUsers();
}

void AuthManager::registerUser(const string& username, const string& email, const string& password) {
  utils.validateEmail(email);
  utils.ensureStrongEnough(password);

  // Verificăm dacă email-ul există deja
  if (findUserByEmail(email)) {
    throw RegistrationException("Email is already taken: " + email);
  }

  string key = hasher.generateKey();
  string hash = hasher.hashPassword(key, password);

  users.push_back(User(username, email, key, hash));
  saveUsers();
}


User* AuthManager::login(const string& email, const string& password) {
  User* user = findUserByEmail(email);
  if (!user) throw LoginFailedException("Email not found");

  if (!hasher.verifyPassword(user->getKey(), password, user->getPasswordHash()))
    throw LoginFailedException("Incorrect password");

  return user;
}

User* AuthManager::findUserByEmail(const string& email) {
  for (auto& u : users) {
    if (u.getEmail() == email) return &u;
  }
  return nullptr;
}

void AuthManager::loadUsers() {
  users.clear();
  ifstream fin(usersCsvFile);
  if (!fin.is_open()) return;

  string line;
  while (getline(fin, line)) {
    stringstream ss(line);
    string username, email, key, hash;

    getline(ss, username, ',');
    getline(ss, email, ',');
    getline(ss, key, ',');
    getline(ss, hash, ',');

    if (!username.empty()) users.push_back(User(username, email, key, hash));
  }
  fin.close();
}

void AuthManager::saveUsers() {
  ofstream fout(usersCsvFile, ios::trunc);
  for (auto& u : users) {
    fout << u.getUsername() << "," 
         << u.getEmail() << "," 
         << u.getKey() << "," 
         << u.getPasswordHash() << "\n";
  }
  fout.close();
}

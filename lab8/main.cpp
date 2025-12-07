#include <iostream>
#include "auth/auth_manager.h"
#include "trips/trip_manager.h"
#include "exceptions/exceptions.h"

using namespace std;

void showUserMenu() {
  cout << "\n1) Search trips\n"
       << "2) Reserve seat\n"
       << "3) Logout\n"
       << "Choose: ";
}

void showOperatorMenu() {
  cout << "\n1) Add trip\n"
       << "2) Remove trip\n"
       << "3) Logout\n"
       << "Choose: ";
}

int main() {
  try {
    AuthManager auth("users.csv");
    TripManager trips("trips.csv");
    PasswordUtils passwordUtils;

    while (true) {
      cout << "Welcome! Choose:\n1) Login\n2) Register\n3) Exit\nChoice: ";
      int choice;
      cin >> choice;
      cin.ignore();

      if (choice == 3) break;

      string email, password, username;
      User* currentUser = nullptr;

      try {
        if (choice == 2) {
          cout << "Enter username: "; getline(cin, username);
          cout << "Enter email: "; getline(cin, email);

          bool passwordOk = false;
          while (!passwordOk) {
            cout << "Enter password: "; getline(cin, password);
            cout << "Confirm password: "; string passwordConfirm; getline(cin, passwordConfirm);

            if (password != passwordConfirm) {
              cerr << "Error: Passwords do not match. Try again.\n";
              continue;
            }

            string strength = passwordUtils.evaluateStrength(password);
            cout << "Password strength: " << strength << "\n";

            if (strength == "weak") {
              cerr << "Error: Password too weak. Enter again.\n";
              continue;
            }

            cout << "Are you sure you want to use this password? (y/n): ";
            char c; cin >> c; cin.ignore();
            if (c == 'y' || c == 'Y') {
              passwordOk = true;
            } else {
              cout << "Enter password again.\n";
            }
          }

          try {
            auth.registerUser(username, email, password);
            cout << "User registered successfully!\n";
          } catch (const RegistrationException& e) {
            cerr << "Registration failed: " << e.what() << "\n";
          }
        }


        cout << "Enter email: "; getline(cin, email);
        cout << "Enter password: "; getline(cin, password);
        currentUser = auth.login(email, password);
        cout << "Login successful! Welcome " << currentUser->getUsername() << "\n";

        bool isOperator = (currentUser->getEmail() == "operator@bus.com"); // simplificat

        int action = 0;
        while (true) {
          if (isOperator) showOperatorMenu();
          else showUserMenu();

          cin >> action;
          cin.ignore();

          if (action == 3) break;

          try {
            if (isOperator) {
              if (action == 1) {
                TripData t;
                cout << "Trip ID: "; getline(cin, t.tripID);
                cout << "From city: "; getline(cin, t.fromCity);
                cout << "To city: "; getline(cin, t.toCity);
                cout << "Date (YYYY-MM-DD): "; getline(cin, t.date);
                cout << "Time (HH:MM): "; getline(cin, t.time);
                cout << "Total seats: "; cin >> t.seatsTotal; t.seatsAvailable = t.seatsTotal; cin.ignore();
                trips.addTrip(t);
                cout << "Trip added.\n";
              } else if (action == 2) {
                string tripID;
                cout << "Trip ID to remove: "; getline(cin, tripID);
                trips.removeTrip(tripID);
                cout << "Trip removed.\n";
              }
            } else {
              if (action == 1) {
                string from, to, date;
                cout << "From city: "; getline(cin, from);
                cout << "To city: "; getline(cin, to);
                cout << "Date (YYYY-MM-DD): "; getline(cin, date);
                vector<Trip> results = trips.searchTrips(from, to, date);
                for (auto& t : results) t.getData().display();
              } else if (action == 2) {
                string tripID, time;
                cout << "Trip ID: "; getline(cin, tripID);
                cout << "Reservation time (HH:MM): "; getline(cin, time);
                trips.reserveSeat(tripID, time);
                cout << "Seat reserved.\n";
              }
            }
          } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
          }
        }

      } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
      }
    }

  } catch (const exception& e) {
    cerr << "Fatal error: " << e.what() << "\n";
  }

  return 0;
}

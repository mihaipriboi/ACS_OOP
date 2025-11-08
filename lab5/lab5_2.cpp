#include <iostream>
#include <string>

using namespace std;

class Employee {
public:
  Employee() {
    name = "Unknown";
    employeeId = 0;
  }

  Employee(const string& n, int id) {
    name = n;
    employeeId = id;
  }

  void displayNameId() const {
    cout << "ID: " << employeeId << ", Name: " << name;
  }

  void displayRole() const {
    cout << ", Role: Employee";
  }

  void displayBonus() const {
    cout << ", Bonus: $100";
  }

  void displayInfo() const {
    displayNameId();
    displayRole();
    displayBonus();
    cout << '\n';
  }

private:
  string name;
  int employeeId;
};

class Manager : public Employee {
public:
  Manager() : Employee() {
    department = "Unassigned";
  }

  Manager(const string& n, int id, const string& d) : Employee(n, id) {
    department = d;
  }

  void displayDepartment() const {
    cout << ", Department: " << department;
  }

  void displayRole() const {
    cout << ", Role: Manager";
  }

  void displayBonus() const {
    cout << ", Bonus: $500";
  }

  void displayInfo() const {
    displayNameId();
    displayRole();
    displayDepartment();
    displayBonus();
    cout << '\n';
  }

private:
  string department;
};

class Director : public Manager {
public:
  Director() : Manager() {
    budgetAllowance = 0.0;
  }

  Director(const string& n, int id, const string& d, double b) : Manager(n, id, d) {
    budgetAllowance = b;
  }

  void displayBudget() const {
    cout << ", Budget: $" << budgetAllowance;
  }

  void displayRole() const {
    cout << ", Role: Director";
  }

  void displayBonus() const {
    cout << ", Bonus: $2000";
  }

  void displayInfo() const {
    displayNameId();
    displayRole();
    displayDepartment();
    displayBudget();
    displayBonus();
    cout << '\n';
  }

private:
  double budgetAllowance;
};

int main() {
  Employee emp("Victor Zanoaga", 101);
  emp.displayInfo();

  Manager mgr("Marcel Proust", 202, "Writing");
  mgr.displayInfo();

  Director dir("Dwayne 'The Rock' Johnson", 303, "Entertainment", 500000.0);
  dir.displayInfo();

  Director dirDefault;
  dirDefault.displayInfo();

  return 0;
}
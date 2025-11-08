open class Employee(
  val name: String = "Unknown",
  val employeeId: Int = 0
) {
  fun displayNameId() {
    print("ID: $employeeId, Name: $name")
  }

  open fun displayRole() {
    print(", Role: Employee")
  }

  open fun displayBonus() {
    print(", Bonus: $100")
  }

  open fun displayInfo() {
    displayNameId()
    displayRole()
    displayBonus()
    println()
  }
}

open class Manager(
  name: String = "Unknown",
  employeeId: Int = 0,
  val department: String = "Unassigned"
) : Employee(name, employeeId) {

  fun displayDepartment() {
    print(", Department: $department")
  }

  override fun displayRole() {
    print(", Role: Manager")
  }

  override fun displayBonus() {
    print(", Bonus: $500")
  }

  override fun displayInfo() {
    displayNameId()
    displayRole()
    displayDepartment()
    displayBonus()
    println()
  }
}

class Director(
  name: String = "Unknown",
  employeeId: Int = 0,
  department: String = "Unassigned",
  val budgetAllowance: Double = 0.0
) : Manager(name, employeeId, department) {

  fun displayBudget() {
    print(", Budget: $${budgetAllowance}")
  }

  override fun displayRole() {
    print(", Role: Director")
  }

  override fun displayBonus() {
    print(", Bonus: $2000")
  }

  override fun displayInfo() {
    displayNameId()
    displayRole()
    displayDepartment()
    displayBudget()
    displayBonus()
    println()
  }
}

fun main() {
  val emp = Employee("Victor Zanoaga", 101)
  emp.displayInfo()

  val mgr = Manager("Marcel Proust", 202, "Writing")
  mgr.displayInfo()

  val dir = Director("Dwayne 'The Rock' Johnson", 303, "Entertainment", 500000.0)
  dir.displayInfo()

  val dirDefault = Director()
  dirDefault.displayInfo()
}
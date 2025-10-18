#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // For std::fill

/**
 * @class Student
 * @brief Represents a student with a name and a dynamic array of grades.
 */
class Student {
private:
    std::string name;
    float* grades;     // Pointer to the dynamically allocated array of grades
    int numGrades;     // Size of the grades array

public:
    /**
     * @brief Constructor for the Student class.
     * @param studentName The name of the student.
     * @param count The number of grades to store (size of the dynamic array).
     */
    Student(const std::string& studentName, int count)
        : name(studentName), numGrades(count) {
        
        std::cout << "\n--- Constructor Called ---\n";
        
        if (numGrades > 0) {
            // 1. Dynamically allocate memory for the grades array
            grades = new float[numGrades];
            // Initialize all grades to 0.0f
            std::fill(grades, grades + numGrades, 0.0f);
            
            std::cout << "Student created: " << name 
                      << " (Allocated memory for " << numGrades << " grades.)\n";
        } else {
            grades = nullptr;
            numGrades = 0;
            std::cout << "Student created: " << name 
                      << " (No grades array allocated.)\n";
        }
    }

    /**
     * @brief Destructor for the Student class.
     * Cleans up the dynamically allocated memory for the grades array.
     */
    ~Student() {
        std::cout << "\n--- Destructor Called ---\n";
        // 2. Deallocate the dynamic memory using delete[]
        if (grades != nullptr) {
            delete[] grades;
            grades = nullptr;
            std::cout << "Student " << name << ": Successfully DEALLOCATED memory for grades.\n";
        } else {
            std::cout << "Student " << name << ": No memory to deallocate (grades was nullptr).\n";
        }
    }

    /**
     * @brief Sets a grade at a specific index.
     * @param index The position in the array.
     * @param grade The grade value (float).
     */
    void setGrade(int index, float grade) {
        if (index >= 0 && index < numGrades) {
            grades[index] = grade;
        } else {
            std::cerr << "Error: Index " << index << " out of bounds for " << name << ".\n";
        }
    }

    /**
     * @brief Changes the student's name.
     * @param newName The new name for the student.
     * OBS: Functie creata de mine.
     */
    void changeName(const std::string& newName) {
        name = newName;
    }

    /**
     * @brief Displays the student's name and all stored grades.
     */
    void displayInfo() const {
        std::cout << "\n=====================================\n";
        std::cout << "Student Name: " << name << "\n";
        std::cout << "Number of Grades: " << numGrades << "\n";
        
        if (numGrades > 0) {
            std::cout << "Grades: [ ";
            for (int i = 0; i < numGrades; ++i) {
                // Use setprecision to show grades nicely
                std::cout << std::fixed << std::setprecision(1) << grades[i];
                if (i < numGrades - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << " ]\n";
        } else {
            std::cout << "Grades: N/A\n";
        }
        std::cout << "=====================================\n";
    }
};

/**
 * @brief Demonstration function to show object lifecycle.
 */
void demoStudentLifecycle() {
    std::cout << "Starting demoStudentLifecycle function...\n";

    // Create a student object with 5 grade slots.
    // Constructor is called here, allocating memory.
    Student s1("Alice Johnson", 5);
    s1.setGrade(0, 95.5f);
    s1.setGrade(1, 88.0f);
    s1.setGrade(2, 92.5f);
    s1.setGrade(3, 79.0f);
    s1.setGrade(4, 98.5f);
    
    s1.displayInfo();
    
    // Create another student with fewer grades
    Student s2("Bob Smith", 3);
    s2.setGrade(0, 75.0f);
    s2.setGrade(1, 85.0f);
    s2.setGrade(2, 65.0f);
    
    s2.displayInfo();

    std::cout << "\nExiting demoStudentLifecycle function.\n";
    // s2's destructor is called first (LIFO order for local variables)
    // s1's destructor is called second
} // Destructors for s2 and s1 are automatically called when they go out of scope.


int main() {
    Student student1("Ovidiu Zanoaga", 4);
    student1.setGrade(0, 8.0f);
    student1.setGrade(1, 9.2f);
    student1.setGrade(2, 7.5f);
    student1.setGrade(3, 2.0f);

    Student student2 = student1;
    student2.changeName("Mihai Priboi");
    student2.setGrade(3, 10.0f);

    student1.displayInfo();
    student2.displayInfo();

    printf("\nObservatie: Deoarece notele sunt stocate dinamic si nu"
           " exista un copy constructor definit care sa faca o copie"
           " corecta a notelor, ambele obiecte acceseaza aceeasi zona"
           " de memorie pentru note. Astfel, modificarea notelor in"
           " studentul 2 va afecta si notele studentului 1.\n");
    return 0;
}

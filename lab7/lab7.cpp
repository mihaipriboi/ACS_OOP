#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Import;

struct StudentData {
  string id;
  int age;
  string gender;
  float study_hours;
  float social_hours;
  float netflix_hours;
  string job;
  float attendance;
  float sleep;
  string diet;
  int exercise;
  string parents_edu;
  string internet;
  int mental_health;
  string extracurricular;
  float score;

  void bind(Import& csv);
  void displayData() const;
};

class Import {
public:
  Import(const char* filename) : filename(strdup(filename)), buffer(nullptr), cursor(nullptr) {
    FILE* file = fopen(filename, "rb");
    if(!file) throw std::runtime_error("File not found");
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    buffer = new char[size + 1];
    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);
    
    cursor = buffer;
  }

  ~Import() {
    free(filename);
    delete[] buffer;
  }

  void skipLine() {
    while (*cursor && *cursor != '\n') cursor++;
    if(*cursor == '\n') cursor++;
  }

  template <typename T>
  bool scanRow(T& object) {
    if(*cursor == '\0') return false;
    object.bind(*this);
    if(*cursor == '\n') cursor++;
    return true;
  }

  template <typename T>
  T scanRow() {
    T obj;
    scanRow(obj);
    return obj;
  }

  template <typename... Args>
  void readRowValues(Args&... args) {
    parseNext(args...);
  }

private:
  char* filename;
  char* buffer;
  char* cursor;

  char* getNextToken() {
    char* start = cursor;
    while(*cursor && *cursor != ',' && *cursor != '\n' && *cursor != '\r') {
      cursor++;
    }
    if(*cursor) {
      *cursor = '\0'; 
      cursor++;       
    }
    return start;
  }

  void parseNext() {}

  template<typename T, typename... Rest>
  void parseNext(T& first, Rest&... rest) {
    char* token = getNextToken();
    convert(first, token);
    parseNext(rest...);
  }

  void convert(int& out, char* s) { out = atoi(s); }
  void convert(float& out, char* s) { out = strtof(s, nullptr); }
  void convert(double& out, char* s) { out = strtod(s, nullptr); }
  void convert(string& out, char* s) { out = s; }
  void convert(char& out, char* s) { out = s[0]; }
};

void StudentData::bind(Import& csv) {
  csv.readRowValues(
    id, age, gender, study_hours, social_hours, netflix_hours, 
    job, attendance, sleep, diet, exercise, parents_edu, 
    internet, mental_health, extracurricular, score
  );
}

void StudentData::displayData() const {
  std::cout << "ID: " << id 
            << " | Age: " << age 
            << " | Gender: " << gender
            << " | Study Hours: " << study_hours
            << " | Job: " << job
            << " | Attendance: " << attendance
            << " | Sleep: " << sleep
            << " | Score: " << score
            << '\n';
}

int main() {
  try {
    Import csv("student_habits_performance-1.csv");
    csv.skipLine();

    StudentData s;
    
    while(csv.scanRow(s)) {
      s.displayData();
    }

  } catch(const exception& e) {
    cerr << e.what() << '\n';
  }
  return 0;
}
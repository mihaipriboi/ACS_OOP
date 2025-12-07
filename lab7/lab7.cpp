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

class Student {
public:
  virtual ~Student() {}
  virtual void load(const StudentData& d) = 0;

  virtual int getAge() const = 0;
  virtual float getStudy() const = 0;
  virtual float getSocial() const = 0;
  virtual string getJob() const = 0;
};

class StudentPolitehnica : public Student {
public:
  void load(const StudentData& d) override { data = d; }
  int getAge() const override { return data.age; }
  float getStudy() const override { return data.study_hours; }
  float getSocial() const override { return data.social_hours; }
  string getJob() const override { return data.job; }

  float computeEfficiency() {
    return data.study_hours - data.social_hours;
  }
private:
  StudentData data;
};

class StudentMedicina : public Student {
public:
  void load(const StudentData& d) override { data = d; }
  int getAge() const override { return data.age; }
  float getStudy() const override { return data.study_hours; }
  float getSocial() const override { return data.social_hours; }
  string getJob() const override { return data.job; }

  bool checkStressLevel() {
    return data.mental_health < 5;
  }
private:
  StudentData data;
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

class StatisticsManager {
public:
  ~StatisticsManager() {
    for(auto s : v) delete s;
  }

  void add(Student* s) { v.push_back(s); }

  float avgAgeMedicina() {
    int c = 0; float sum = 0;
    for(auto s : v) {
      if(dynamic_cast<StudentMedicina*>(s)) {
        c++; 
        sum += s->getAge();
      }
    }
    return c ? sum / c : 0;
  }

  void upbStudySocial(float& a, float& b) {
    int c = 0; 
    float s1 = 0, s2 = 0;
    for(auto s : v) {
      if(dynamic_cast<StudentPolitehnica*>(s)) {
        c++; 
        s1 += s->getStudy(); 
        s2 += s->getSocial();
      }
    }
    if(!c) { 
      a = 0; 
      b = 0; 
      return; 
    }
    a = s1 / c; 
    b = s2 / c;
  }

  int countPartTime() {
    int c = 0;
    for(auto s : v) 
      if(s->getJob() == "Yes") 
        c++;
    return c;
  }
private:
  vector<Student*> v;
};


int main() {
  try {
    Import csv("student_habits_performance-1.csv");
    csv.skipLine();

    StatisticsManager manager;
    StudentData d;

    while(csv.scanRow(d)) {
      Student* s;

      if(rand() % 2 == 0) 
        s = new StudentPolitehnica();
      else 
        s = new StudentMedicina();

      s->load(d);
      manager.add(s);
    }

    float medie_medicina = manager.avgAgeMedicina();
    cout << "1) Varsta medie a studentilor de la Medicina: " 
         << medie_medicina << "\n";

    float study_upb, social_upb;
    manager.upbStudySocial(study_upb, social_upb);

    cout << "2) Timp mediu studiu UPB: " << study_upb << "\n";
    cout << "   Timp mediu social UPB: " << social_upb << "\n";

    int part_time = manager.countPartTime();
    cout << "3) Studentii cu job part-time: " << part_time << "\n\n";
  } catch(const exception& e) {
    cerr << "Eroare: " << e.what() << '\n';
  }

  return 0;
}
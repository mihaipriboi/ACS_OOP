#include <iostream>
#include <string>

using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))

class Text {
public:
  Text() {
    content = "";
  }

  Text(const string& s) {
    content = s;
  }

  Text operator+(const Text& other) const {
    Text result;
    result.content = this->content + other.content;
    return result;
  }

  void operator-() {
    size_t posDot = content.find('.');
    size_t posComma = content.find(',');
    size_t pos = string::npos;

    if(posDot != string::npos && posComma != string::npos) {
      pos = min(posDot, posComma);
    } else if(posDot != string::npos) {
      pos = posDot;
    } else if(posComma != string::npos) {
      pos = posComma;
    }

    if(pos != string::npos)
      content = content.substr(0, pos);
  }

  void afiseaza() const {
    cout << content << '\n';
  }

private:
  string content;
};

int main() {
  Text t1("Hello,");
  Text t2(" world.FizzBuzz.");
  
  Text t3 = t1 + t2;
  cout << "Dupa concatenare: ";
  t3.afiseaza();

  -t3;
  cout << "Dupa separare: ";
  t3.afiseaza();

  Text t4("I use Arch btw");
  cout << "t4: ";
  t4.afiseaza();
  -t4;
  cout << "t4 dupa separare: ";
  t4.afiseaza();

  Text t5("Foo.Bar");
  cout << "t5: ";
  t5.afiseaza();
  -t5;
  cout << "t5 dupa separare: ";
  t5.afiseaza();

  return 0;
}
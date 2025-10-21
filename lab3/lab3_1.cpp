#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Exchange {
private:
  int money;
  static int count;
  static int over3000Count;

public:
  Exchange() {
    money = rand() % 5001;

    count++;
    over3000Count += (money > 3000);
  }

  static int getCount() { return count; }
  static int getOver3000Count() { return over3000Count; }
};

int Exchange::count = 0;
int Exchange::over3000Count = 0;

int main() {
  srand(static_cast<unsigned int>(time(0)));

  vector<Exchange> exchanges;

  time_t now = time(0);
  tm *ltm = localtime(&now);
  int currentDay = ltm->tm_mday;

  for(int i = 0; i < currentDay; ++i)
    exchanges.push_back(Exchange());

  printf("Total objects created: %d\n", Exchange::getCount());
  printf("Objects with money > 3000: %d\n", Exchange::getOver3000Count());

  return 0;
}
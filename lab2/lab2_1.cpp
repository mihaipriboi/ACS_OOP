#include <stdio.h>
#include <ctime>

class TimeLogger {
public:
  TimeLogger() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    printf("Object created on: %d/%d/%d %d:%d:%d\n",
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year,
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    int h = 23 - ltm->tm_hour;
    int m = 59 - ltm->tm_min;
    int s = 59 - ltm->tm_sec;
    printf("Time left until the end of the day: %d hours, %d minutes, %d seconds\n", h, m, s);
  }
};

int main() {
  TimeLogger obj;
  return 0;
}
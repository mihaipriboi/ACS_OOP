#ifndef TRIP_H
#define TRIP_H

#include <string>
#include <vector>

using namespace std;

struct TripData {
  string tripID;
  string fromCity;
  string toCity;
  string date;        // format YYYY-MM-DD
  string time;        // format HH:MM
  int seatsTotal;
  int seatsAvailable;

  void display() const;
};

class Trip {
public:
  Trip();
  Trip(const TripData& data);

  TripData getData() const;
  void setData(const TripData& data);

private:
  TripData data;
};

#endif

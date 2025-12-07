#ifndef TRIP_MANAGER_H
#define TRIP_MANAGER_H

#include <string>
#include <vector>
#include "trip.h"
#include "../exceptions/exceptions.h"

using namespace std;

class TripManager {
public:
  TripManager(const string& tripsCsvFile);

  // Operator
  void addTrip(const TripData& trip);
  void removeTrip(const string& tripID);

  // User
  vector<Trip> searchTrips(const string& fromCity, const string& toCity, const string& date);
  void reserveSeat(const string& tripID, const string& reservationTime);

  // Load/Save
  void loadTrips();
  void saveTrips();

private:
  string tripsCsvFile;
  vector<Trip> trips;

  Trip* findTripByID(const string& tripID);

  void validateTripData(const TripData& trip);
  void validateCity(const string& city);
};

#endif

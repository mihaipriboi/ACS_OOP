#include "trip.h"
#include <iostream>

Trip::Trip() {}

Trip::Trip(const TripData& d) : data(d) {}

TripData Trip::getData() const { return data; }

void Trip::setData(const TripData& d) { data = d; }

void TripData::display() const {
  cout << "Trip ID: " << tripID
       << " | From: " << fromCity
       << " | To: " << toCity
       << " | Date: " << date
       << " | Time: " << time
       << " | Seats: " << seatsAvailable << "/" << seatsTotal
       << '\n';
}

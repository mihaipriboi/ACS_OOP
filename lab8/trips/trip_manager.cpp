#include "trip_manager.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

TripManager::TripManager(const string& file) : tripsCsvFile(file) {
  loadTrips();
}

void TripManager::addTrip(const TripData& trip) {
  validateTripData(trip);
  validateCity(trip.fromCity);
  validateCity(trip.toCity);

  trips.push_back(Trip(trip));
  saveTrips();
}

void TripManager::removeTrip(const string& tripID) {
  for (auto it = trips.begin(); it != trips.end(); ++it) {
    if (it->getData().tripID == tripID) {
      trips.erase(it);
      saveTrips();
      return;
    }
  }
  throw TripNotFoundException("Trip ID " + tripID);
}

vector<Trip> TripManager::searchTrips(const string& fromCity, const string& toCity, const string& date) {
  vector<Trip> result;
  for (auto& t : trips) {
    TripData d = t.getData();
    if (d.fromCity == fromCity && d.toCity == toCity && d.date == date) {
      result.push_back(t);
    }
  }
  if (result.empty()) throw TripNotFoundException("No trips found for given criteria");
  return result;
}

void TripManager::reserveSeat(const string& tripID, const string& reservationTime) {
  Trip* trip = findTripByID(tripID);
  if (!trip) throw TripNotFoundException("Trip ID " + tripID);

  TripData d = trip->getData();
  if (d.seatsAvailable <= 0) throw ReservationException("No seats available");

  // We could validate reservationTime format here if needed
  d.seatsAvailable--;
  trip->setData(d);
  saveTrips();
}

Trip* TripManager::findTripByID(const string& tripID) {
  for (auto& t : trips) {
    if (t.getData().tripID == tripID) return &t;
  }
  return nullptr;
}

void TripManager::validateTripData(const TripData& trip) {
  // Validate date format YYYY-MM-DD
  if (trip.date.size() != 10 || trip.date[4] != '-' || trip.date[7] != '-') {
    throw InvalidTripDataException("Invalid date format");
  }

  // Validate time format HH:MM
  if (trip.time.size() != 5 || trip.time[2] != ':') {
    throw InvalidTripDataException("Invalid time format");
  }

  // Check seats
  if (trip.seatsTotal <= 0) {
    throw InvalidTripDataException("Total seats must be positive");
  }
}

void TripManager::validateCity(const string& city) {
  for (char c : city) {
    if (!isalpha(c) && c != ' ') throw InvalidCityException(city);
  }
}

void TripManager::loadTrips() {
  trips.clear();
  ifstream fin(tripsCsvFile);
  if (!fin.is_open()) return;

  string line;
  while (getline(fin, line)) {
    stringstream ss(line);
    TripData d;
    string seatsTotalStr, seatsAvailableStr;

    getline(ss, d.tripID, ',');
    getline(ss, d.fromCity, ',');
    getline(ss, d.toCity, ',');
    getline(ss, d.date, ',');
    getline(ss, d.time, ',');
    getline(ss, seatsTotalStr, ',');
    getline(ss, seatsAvailableStr, ',');

    d.seatsTotal = stoi(seatsTotalStr);
    d.seatsAvailable = stoi(seatsAvailableStr);

    trips.push_back(Trip(d));
  }
  fin.close();
}

void TripManager::saveTrips() {
  ofstream fout(tripsCsvFile, ios::trunc);
  for (auto& t : trips) {
    TripData d = t.getData();
    fout << d.tripID << "," 
         << d.fromCity << "," 
         << d.toCity << "," 
         << d.date << "," 
         << d.time << "," 
         << d.seatsTotal << "," 
         << d.seatsAvailable << "\n";
  }
  fout.close();
}

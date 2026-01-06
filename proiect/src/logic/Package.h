#pragma once

#include <string>

/* Represents a delivery order generated at the Hub */
struct Package {
  int id;
  int destX, destY;
  int reward;        /* 200 - 800 credits */
  int deadline;      /* 10 - 20 ticks */
  int spawnTick;
  bool delivered;

  Package(int id, int dx, int dy, int r, int dl, int st) 
    : id(id), destX(dx), destY(dy), reward(r), 
      deadline(dl), spawnTick(st), delivered(false) {}
};
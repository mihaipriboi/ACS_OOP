#pragma once

#include <string>

enum class PackageStatus { AT_HUB, IN_TRANSIT, DELIVERED };

struct Package {
  int id;
  int destX, destY;
  int reward;        /* 200 - 800 credits */
  int deadline;      /* 10 - 20 ticks */
  int spawnTick;
  PackageStatus status;
  int carrierId; // ID of the agent carrying it (-1 if at Hub)

  Package(int id, int dx, int dy, int r, int dl, int st) 
    : id(id), destX(dx), destY(dy), reward(r), 
      deadline(dl), spawnTick(st), status(PackageStatus::AT_HUB), carrierId(-1) {}
};
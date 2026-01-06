#pragma once

#include "Map.h"

class IMapGenerator {
public:
  virtual ~IMapGenerator() {}
  virtual Map* generate() = 0;
};
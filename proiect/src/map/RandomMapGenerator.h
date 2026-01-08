#pragma once

#include "IMapGenerator.h"
#include "../core/ConfigManager.h"

class RandomMapGenerator : public IMapGenerator {
public:
  Map* generate() override;
};
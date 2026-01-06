#pragma once

#include "IMapGenerator.h"
#include "../core/ConfigManager.h"

class ProceduralGenerator : public IMapGenerator {
public:
  Map* generate() override;
};
#pragma once

#include "IMapGenerator.h"

#include <string>

class FileMapLoader : public IMapGenerator {
private:
  string filename;
public:
  FileMapLoader(const string& fname) : filename(fname) {}
  Map* generate() override;
};
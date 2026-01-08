#pragma once

#include <string>

enum class CellType {
  WALL = 0,
  SPACE = 1,
  HUB = 2,
  STATION = 3,
  CLIENT = 4,
  PATH = 5
};

enum class ValidationType {
  STANDARD = 0,
  DRONE = 1
};

/* Arrays to convert enum to char for display/file saving */
const char CELL_CHARS[] = {'#', '.', 'B', 'S', 'D', 'P'};
const std::string CELL_CHARS_TERMINAL[] = {"\u2588", "\u00b7", "\u25a3", "\u2295", "\u2302", "\u25CF"};
//                                             █         ·         ▣        ⊕        ⌂         ●
#include "FileMapLoader.h"
#include "MapExceptions.h"

Map* FileMapLoader::generate() {
  FILE* file = fopen(filename.c_str(), "r");
  if(!file) throw FileMissingException(filename);

  int r, c;
  if(fscanf(file, "%d %d", &r, &c) != 2) {
    fclose(file);
    throw MapParseException("Invalid header (size missing)");
  }

  Map* map = new Map(r, c);
  char cell;
  int hubCount = 0;
  int clientCount = 0;

  for(int i = 0; i < r; i++) {
    for(int j = 0; j < c; j++) {
      do {
        cell = fgetc(file);
      } while(cell == ' ' || cell == '\n' || cell == '\r');

      if(cell == EOF) {
        delete map;
        fclose(file);
        throw MapParseException("Unexpected end of file (dimensions mismatch)");
      }

      CellType type;
      bool validChar = true;
      if(cell == '#') type = CellType::WALL;
      else if(cell == '.') type = CellType::SPACE;
      else if(cell == 'B') { type = CellType::HUB; hubCount++; }
      else if(cell == 'S') type = CellType::STATION;
      else if(cell == 'D') { type = CellType::CLIENT; clientCount++; }
      else validChar = false;

      if(!validChar) {
        delete map;
        fclose(file);
        throw MapParseException("Invalid character in map: " + string(1, cell));
      }
      map->setCell(i, j, type);
    }
  }

  fclose(file);

  if(hubCount == 0) { delete map; throw MapValidationException("Map must contain a Base (B)"); }
  if(clientCount == 0) { delete map; throw MapValidationException("Map must contain at least one Client (D)"); }

  return map;
}
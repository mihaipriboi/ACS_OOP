#pragma once

#include <cstdio>
#include <cstring>

class UIHelper {
public:
  static void printHeader(const char* text = "") {
    int totalWidth = 40;
    int textLen = strlen(text);
    if(textLen == 0) {
      for(int i = 0; i < totalWidth; i++) printf("~");
    } else {
      int side = (totalWidth - textLen - 2) / 2;
      for(int i = 0; i < side; i++) printf("~");
      printf(" %s ", text);
      for(int i = 0; i < (totalWidth - textLen - 2 - side); i++) printf("~");
    }
    printf("\n");
  }
};
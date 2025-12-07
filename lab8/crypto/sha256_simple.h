#ifndef SHA256_SIMPLE_H
#define SHA256_SIMPLE_H

#include <string>
#include <vector>
#include <cstdint>

using namespace std;

class SHA256 {
public:
  SHA256();
  vector<unsigned char> compute(const string& input);
  static string toHex(const vector<unsigned char>& data);

private:
  static uint32_t rotr(uint32_t x, uint32_t n);
  static const uint32_t K[64];
};

#endif

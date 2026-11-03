// Test example: build with `g++ -std=c++11 main.cpp MeshCSC.cpp -o meshcsc_demo`
#include <cstdio>
#include <string>
#include "MeshCSC.h"

int main() {
  meshcsc::MeshCSC codec;
  const char* samples[] = {
    "node battery low signal weak",
    "i sold the fuel and went to the base",
    "he sells water, she sold food, they have gone",
    "need medical help at the bridge, road blocked!",
    "weather report: wind and rain, temperature low",
    "go to xyzzy now",
    "Unknown Callsign KX9 ? ok",
  };
  int failures = 0;
  std::printf("Dictionary entries: %zu\n", codec.size());
  for (const char* s : samples) {
    std::string in = s, c = codec.compress(in), d = codec.decompress(c);
    bool ok = (d == in);
    if (!ok) ++failures;
    std::printf("[%s] %zu -> %zu bytes (%.0f%% saved)\n  in : %s\n  out: %s\n  back: %s\n",
                ok ? "OK" : "FAIL", in.size(), c.size(),
                100.0 * (1.0 - (double)c.size() / (double)in.size()),
                in.c_str(), c.c_str(), d.c_str());
  }
  return failures ? 1 : 0;
}

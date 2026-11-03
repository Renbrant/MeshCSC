# MeshCSC
**Mesh Compact Semantic Codec** — ultra-compact semantic text compression for LoRa and mesh networks (MeshCore, Meshtastic), written in C++ for ESP32 (ESP-IDF / Arduino).

MeshCSC turns natural English words into 1–2 character tokens before transmission and restores them on the receiving node. Shorter payloads mean less airtime, fewer collisions and lower battery use.

## Concept
LoRa payloads are tiny and airtime is expensive. Instead of byte-level compression (inefficient on short messages), MeshCSC does *semantic* compression with a fixed dictionary of ~3,500 words/verb forms shared by both ends:

```
in : need medical help at the bridge, road blocked!
out: nb ml hp at tj b2, rm b3!
```

### Core rules
1. **No isolated punctuation** – no code is punctuation only; punctuation in the text stays attached to the neighbouring word.
2. **1 and 2 characters only** – every code is 1–2 chars of `A-Z a-z 0-9` (all-digit codes are avoided so numbers in telemetry are never mistaken for codes).
3. **Distinct tense mappings** – present, past and participle forms have separate codes (`sell=sl`, `sold=sd`, `go=go`, `went=wn`, `gone=gn`).
4. **Fallback** – words not in the dictionary pass through intact. The only exception: an unknown word that happens to equal a code (or starts with `_`) is prefixed with `_` so decompression is lossless.

Codes are unique, so the mapping is bijective. Matching is case-sensitive: dictionary words are lowercase; other tokens pass through unchanged.

## Installation
- **Arduino / PlatformIO**: copy `MeshCSC.h`, `MeshCSC.cpp`, `dictionary_3500.h` into your sketch or `lib/MeshCSC/`.
- **ESP-IDF**: add the files to a component and list `MeshCSC.cpp` in `idf_component_register(SRCS ...)`.
- **Host (testing)**: `g++ -std=c++11 main.cpp MeshCSC.cpp -o meshcsc_demo && ./meshcsc_demo`

## Usage
```cpp
#include "MeshCSC.h"

meshcsc::MeshCSC codec;
std::string tx = codec.compress("node battery low signal weak"); // "nd bt lw sg 5q"
std::string rx = codec.decompress(tx);                           // original text
```

Both nodes **must** use the same `dictionary_3500.h`.

## Memory
The dictionary table lives in flash (`PROGMEM`). At construction it is indexed into two `std::unordered_map`s (a few hundred KB of heap on ESP32; construct once and reuse).

## Bandwidth savings
Measured with `main.cpp` on telemetry/field-style sentences:

| Message | Original | Compressed | Saved |
|---|---|---|---|
| node battery low signal weak | 28 B | 14 B | ~50% |
| weather report: wind and rain, temperature low | 46 B | 22 B | ~52% |
| need medical help at the bridge, road blocked! | 46 B | 25 B | ~46% |
| go to xyzzy now (unknown word) | 15 B | 14 B | ~7% |

Typical savings are 30–55% on dictionary-heavy text, 0% on text with no known words. Fewer bytes on the air roughly means proportionally less airtime.

## License
See [LICENSE](LICENSE).

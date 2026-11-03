#pragma once
// MeshCSC - Mesh Compact Semantic Codec
// Bidirectional semantic text compression for LoRa/mesh radios (MeshCore, Meshtastic).
#include <string>
#include <unordered_map>
#include "dictionary_3500.h"

namespace meshcsc {

class MeshCSC {
public:
  // Builds lookup tables from the flash-resident (PROGMEM) dictionary.
  MeshCSC();

  // Replaces known words with 1-2 char codes. Unknown words pass through intact.
  // Spaces are preserved; leading/trailing punctuation stays attached to the word.
  std::string compress(const std::string& text) const;

  // Restores the original words from codes.
  std::string decompress(const std::string& text) const;

  size_t size() const { return wordToCode_.size(); }

  // Prefix marking a literal token that would otherwise be read as a code
  // (or that already starts with the prefix).
  static constexpr char ESCAPE = '_';

private:
  std::unordered_map<std::string, std::string> wordToCode_;
  std::unordered_map<std::string, std::string> codeToWord_;
};

}  // namespace meshcsc

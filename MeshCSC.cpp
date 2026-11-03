#include "MeshCSC.h"
#include <cctype>

namespace meshcsc {

namespace {
bool isAlnum(char c) { return std::isalnum(static_cast<unsigned char>(c)) != 0; }

// Splits a space-free token into leading punctuation, core and trailing punctuation.
void splitToken(const std::string& tok, std::string& lead, std::string& core, std::string& trail) {
  size_t b = 0, e = tok.size();
  while (b < e && !isAlnum(tok[b])) ++b;
  while (e > b && !isAlnum(tok[e - 1])) --e;
  if (b == e) {  // no alphanumerics: leave intact
    lead = tok; core.clear(); trail.clear();
    return;
  }
  lead = tok.substr(0, b);
  core = tok.substr(b, e - b);
  trail = tok.substr(e);
}

template <typename F>
std::string mapTokens(const std::string& text, F fn) {
  std::string out;
  out.reserve(text.size());
  size_t i = 0;
  while (i < text.size()) {
    if (text[i] == ' ') { out += ' '; ++i; continue; }
    size_t j = i;
    while (j < text.size() && text[j] != ' ') ++j;
    std::string lead, core, trail;
    splitToken(text.substr(i, j - i), lead, core, trail);
    out += lead;
    if (!core.empty()) out += fn(core);
    out += trail;
    i = j;
  }
  return out;
}
}  // namespace

MeshCSC::MeshCSC() {
  wordToCode_.reserve(MESHCSC_DICT_SIZE);
  codeToWord_.reserve(MESHCSC_DICT_SIZE);
  for (size_t i = 0; i < MESHCSC_DICT_SIZE; ++i) {
    wordToCode_[MESHCSC_DICT[i].word] = MESHCSC_DICT[i].code;
    codeToWord_[MESHCSC_DICT[i].code] = MESHCSC_DICT[i].word;
  }
}

std::string MeshCSC::compress(const std::string& text) const {
  return mapTokens(text, [this](const std::string& w) -> std::string {
    auto it = wordToCode_.find(w);
    if (it != wordToCode_.end()) return it->second;
    // Unknown word: intact, unless it could be mistaken for a code.
    if (codeToWord_.count(w) || w[0] == ESCAPE) return std::string(1, ESCAPE) + w;
    return w;
  });
}

std::string MeshCSC::decompress(const std::string& text) const {
  return mapTokens(text, [this](const std::string& t) -> std::string {
    if (t[0] == ESCAPE && t.size() > 1) return t.substr(1);
    auto it = codeToWord_.find(t);
    return it != codeToWord_.end() ? it->second : t;
  });
}

}  // namespace meshcsc

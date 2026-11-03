# MeshCSC — Mesh Compact Semantic Codebook

MeshCSC is the shared word-to-code codebook for mesh communications. This repository stores dictionary data; each developer implements the encoder and decoder for their own software.

## English dictionary

The current English dictionary is [`dictionaries/english.json`](https://raw.githubusercontent.com/Renbrant/MeshCSC/main/dictionaries/english.json). It has 3,750 unique word-to-code mappings. Its JSON contains only the message wire ID and the mapping table.

The selection contains 3,500 high-frequency English word forms and 250 curated mesh, radio, emergency, search-and-rescue, navigation, and communications terms. The most frequent words receive the shortest codes. Codes are unique, 1–2 ASCII letters or digits, and no code consists only of digits.

## Message wire ID

Every codebook-encoded message starts with exactly one ASCII alphanumeric byte, with no separator between the ID and the encoded body:

```text
E<encoded-body>
```

The receiver reads this first byte, selects the dictionary with the matching ID, removes the ID, and decodes the remaining body. IDs are case-sensitive. An unknown ID must not be decoded using a guessed dictionary.

The ID is globally unique to a language and an immutable dictionary mapping. Do not reuse an ID, even after retiring a dictionary. Assign a new ID whenever the word-to-code mappings change. The ID alphabet is case-sensitive Base62 (`A-Z`, `a-z`, `0-9`), for 62 available dictionary/version IDs. If those are exhausted, the header format must be extended before adding more IDs.

| Wire ID | Language | Dictionary version | Status |
|---|---|---:|---|
| `E` | English (`en`) | `2.0.0` | Current |

Each dictionary JSON stores its assigned `wire_id`. Keep this registry table in sync when adding another language or version. The one-byte header adds one byte to each encoded message and counts toward the radio payload limit.

## Examples

These everyday English sentences show the wire payload produced by the current dictionary. The first sentence is a natural English version of the example “Bom dia…”. Inputs are normalized to lowercase before lookup; decoded words are lowercase, so capitalization is not preserved. Punctuation stays attached to its token in these examples.

| Original phrase | Transmitted payload | Original chars | Payload chars | Reduction |
|---|---|---:|---:|---:|
| `Good morning, did you watch the game today? I could barely stay in my chair. I almost had a heart attack.` | `EaA gJ, a3 k hc a ch dn? g aI Ys hb f A HN. g fp ab e gE nA.` | 105 | 60 | 45 (42.9%) |
| `I am running a little late, but I will be there in about ten minutes.` | `Eg bM kc e bY f1, z g N p ae f Q nR gI.` | 69 | 39 | 30 (43.5%) |
| `Can you pick up some milk and bread on your way home?` | `EM k ph R at IM d Ud m K a0 b4?` | 53 | 31 | 22 (41.5%) |
| `I left my keys on the kitchen table, and now I cannot find them.` | `Eg cC A 0Z m a KS mn, d av g lR b2 au.` | 64 | 38 | 26 (40.6%) |
| `We had a great time at dinner last night, and the food was really good.` | `EI ab e bx ah v BR by cG, d a eW o be aA.` | 71 | 41 | 30 (42.3%) |

Counts include spaces, punctuation, and the one-character `E` wire ID. The ID is attached to the first code with no separator. Reduction is calculated as `(original characters − payload characters) ÷ original characters`. Every word in these examples is present in the English dictionary.

## Case and decoding rules

Normalize source words to lowercase before lookup. Decoding returns lowercase words, so original capitalization is not preserved.

Wire IDs and encoded code tokens remain case-sensitive. Do not lowercase the ID or encoded body after transmission; uppercase and lowercase code characters represent different mappings. Implementations must agree on tokenization and literal escaping.

## Selection source and attribution

The 3,500-word frequency core was selected from the 25,000-word English `wordfreq` export published at [aparrish/wordfreq-en-25000](https://github.com/aparrish/wordfreq-en-25000). The export does not state its exact upstream build. The `wordfreq` project documents a frequency snapshot through about 2021 and describes a broad mix of sources, including Google Books Ngrams, the Leeds Internet Corpus, Wikipedia, ParaCrawl, OpenSubtitles 2018, SUBTLEX, NewsCrawl, GlobalVoices, OSCAR, Twitter, and Reddit. The additional 250 terms were curated for mesh communications, emergency response, SAR, and navigation.

In the filtered wordfreq export, the 3,500 frequency-ranked terms account for an estimated 87.4% of token frequency; the full 3,750-entry dictionary accounts for about 87.6%. These figures describe that reference export, not actual mesh traffic.

The frequency data is derived from `wordfreq` and is distributed under **CC BY-SA 4.0** where applicable. Attribution: Robyn Speer, [rspeer/wordfreq](https://github.com/rspeer/wordfreq), [project citation](https://doi.org/10.5281/zenodo.7199437). The upstream sources also require credit for SUBTLEX authors, including Marc Brysbaert et al., and attribution to OpenSubtitles 2018. See the upstream project’s [license and attribution notes](https://github.com/rspeer/wordfreq#license). The root `LICENSE` applies to repository-authored material; the English dataset follows the data license stated here.

## Adding languages and versions

Add one JSON file per language under `dictionaries/`, such as `portuguese.json`. Give every language/version mapping a new, globally unique one-character wire ID and register the ID, language, version, and status in the table above. Keep old mappings and IDs available so archived messages remain decodable.

Any change to an existing word-to-code mapping is a new dictionary version and requires a new wire ID. Pin the repository commit or release tag when building interoperable software.

## Scope

This repository contains codebook data and its maintenance documentation only. It does not provide an encoder, decoder, radio protocol, firmware, or application.

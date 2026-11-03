# MeshCSC — Mesh Compact Semantic Codebook

MeshCSC is the shared English word-to-code codebook for mesh communications. The repository stores the dictionary data; each developer builds an encoder and decoder for their own software.

## English dictionary

The current release is [`dictionaries/english.json`](https://raw.githubusercontent.com/Renbrant/MeshCSC/main/dictionaries/english.json). It contains **3,750 entries**:

- 3,500 high-frequency English word forms selected from a broad frequency list
- 250 curated mesh, radio, emergency, search-and-rescue, navigation, and communications terms

The most frequent terms receive the shortest codes. Every code is unique, 1–2 ASCII letters or digits, and no code consists only of digits.

## Case handling

Normalize source words to lowercase before lookup. The codebook keys are lowercase, and decoding returns lowercase words, so capitalization is intentionally not preserved.

Code tokens are case-sensitive. Do not lowercase encoded codes: upper- and lowercase letters distinguish different codes and are needed to support the full dictionary size. Implementations must also agree on tokenization and literal escaping.

## Data format

The JSON contains `format_version`, `dictionary_version`, language metadata, normalization rules, selection and attribution metadata, and a `word_to_code` mapping.

The frequency-ranked core is derived from the cited `wordfreq` English frequency export. The export does not state its exact upstream version. The wordfreq project documents its frequency data as a snapshot through about 2021; the export combines a broad mix of sources. Mesh and emergency terms were curated to supplement that broad English core; they are not claimed to be frequency-ranked.

The English dictionary is released under **CC BY-SA 4.0** where applicable to the derived frequency data. The export and upstream project attribution, source notes, and license link are embedded in the JSON so they travel with the shared file. The root `LICENSE` applies to repository-authored material; the dictionary's embedded data license governs the English dataset.

## Adding languages and updating mappings

Add one file per language under `dictionaries/`, such as `portuguese.json`. Keep each language's words separate and include its language tag and normalization rules.

The current English mapping is version `2.0.0`; this revision replaces the pre-release word selection and remaps codes. Pin a Git commit or release tag when building interoperable software. Future changes to existing mappings must be treated as breaking changes and documented.

## Scope

This repository contains codebook data and its maintenance documentation only. It does not provide an encoder, decoder, protocol, firmware, or application.

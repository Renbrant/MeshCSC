# MeshCSC — Mesh Compact Semantic Codebook

MeshCSC (Mesh Compact Semantic Codebook) is a shared word-to-code dictionary for mesh-network projects. This repository maintains the codebook data only; each developer or project implements its own encoder and decoder using the language dictionary it needs.

## English

The current dictionary is [`dictionaries/english.json`](https://raw.githubusercontent.com/Renbrant/MeshCSC/main/dictionaries/english.json). It is JSON, so applications can fetch and parse it directly or package it with firmware.

The file contains:

- `format_version`: structure version for the JSON schema
- `language.name`: human-readable language name (`English`)
- `language.tag`: language tag (`en`)
- `word_to_code`: mapping from each word to its assigned code

Words and codes are case-sensitive. Codes are unique and use 1–2 ASCII letters or digits, with no punctuation. The English dictionary currently contains 3,500 entries.

## Adding languages

Add one JSON file per language under `dictionaries/`, using a descriptive lowercase filename, such as `portuguese.json`. Set the language name and language tag in the file metadata. Keep mappings separate by language.

## Interoperability and updates

Implementations that exchange encoded text must use the same dictionary revision and compatible tokenization and escaping rules. Pin a Git commit or release tag; dictionary changes can affect wire compatibility.

Keep existing word-to-code assignments stable. Additions must use unused codes. If an assignment changes or is removed, document it as a breaking dictionary revision.

## Scope

This repository contains dictionary data and its maintenance documentation only. It does not define a codec, protocol, tokenizer, firmware, or application.

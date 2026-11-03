# MeshCSC Dictionary

MeshCSC is a shared English word-to-code dictionary for mesh-network projects. This repository maintains the dictionary data only; encoder and decoder programs are developed separately by each project or developer.

## Data format

[`dictionary.csv`](dictionary.csv) is the canonical source:

- UTF-8 CSV with the header `word,code`
- One word and its assigned code per row
- Words and codes are case-sensitive
- Codes are unique, 1–2 ASCII letters or digits, and contain no punctuation
- The current table contains 3,500 entries

The file is language-neutral data. Implementations can load it at build time or convert it into a format that suits their target.

## Interoperability and updates

Two implementations can exchange encoded text only when they use the same dictionary revision and compatible tokenization/escaping rules. Pin a Git commit or release tag when building a product; do not assume that a future dictionary revision is wire-compatible.

Existing word-to-code assignments should remain stable. Additions must use unused codes. If an assignment must change or be removed, treat that as a breaking dictionary revision and document it in the change.

## Scope

This repository does not provide a codec, protocol, tokenizer, firmware, or application. Each consuming project is responsible for defining those behaviors and for testing its implementation against the dictionary it uses.

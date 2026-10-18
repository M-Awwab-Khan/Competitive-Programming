# Submission templates

- [Minimal C++ problem starter](cpp/problem.cpp) — used by `make new LANG=cpp NAME=...`.
- [Minimal Python problem starter](python/problem.py) — used by `make new LANG=python NAME=...`.
- [Original C++ template](cpp/cp-template.cpp) — preserved macros and demo code; its local debug helper is under `practice/legacy/`.
- [Original Python template](python/py-template.py) — preserved custom FastIO version.
- [GNU C++17 speed-programming reference snippets](cpp/sp-reference.hpp) — generated from the [full cheat sheet](../notes/contest-prep/div3-speed-programming.md); paste needed routines for submission.

Run `make new NAME=A LANG=cpp` from the repository root to create a standalone problem folder with sample files. Edit the minimal starters here to customize future problems; existing sources are never changed. The C++ starter keeps `#include "bits/stdc++.h"`; Make manages the precompiled header. Existing editor snippets remain in `.vscode/`.

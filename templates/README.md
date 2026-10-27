# Submission templates

- [Minimal C++ problem starter](cpp/problem.cpp) — used by `make new problem.cpp`.
- [Minimal Python problem starter](python/problem.py) — used by `make new problem.py`.
- [Colored C++ debug helpers](cpp/debugging.hpp) — adapted from the preserved legacy helper; injected by `make debug`.
- [Original C++ template](cpp/cp-template.cpp) — preserved macros and demo code; its local debug helper is under `practice/legacy/`.
- [Original Python template](python/py-template.py) — preserved custom FastIO version.
- [GNU C++17 speed-programming reference snippets](cpp/sp-reference.hpp) — generated from the [full cheat sheet](../notes/contest-prep/div3-speed-programming.md); paste needed routines for submission.

Run `make new A.cpp` from the repository root to create a standalone problem folder with sample files. Edit the minimal starters here to customize future problems; existing sources are never changed. The C++ starter keeps `#include "bits/stdc++.h"`; Make manages the precompiled header. Existing editor snippets remain in `.vscode/`.

Use `debug(x, values)` and `debugArr(array, length)` in new C++ starters. `make debug A.cpp` enables the colored stderr helpers, compiler warnings, AddressSanitizer and UndefinedBehaviorSanitizer, then checks samples. Ordinary builds discard these calls. Existing sources are not rewritten. See the [debug workflow](../notes/tooling/problem-workflow.md#debug-builds-and-colored-stderr).

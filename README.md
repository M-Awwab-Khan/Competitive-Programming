# Competitive Programming

My competitive programming solutions, organized by the patterns used to solve them.

**[Browse every problem](catalog/INDEX.md)** · **[Browse by tag](catalog/TAGS.md)** · **[Categories](solutions/README.md)** · **[Classification review](catalog/REVIEW.md)** · **[Pattern notes](notes/patterns/INDEX.md)** · **[Organization log](ORGANIZATION_LOG.md)**

## Speed programming preparation

**[Div. 3 contest cheat sheet](notes/contest-prep/quick-reference.md)** · **[Full preparation reference](notes/contest-prep/div3-speed-programming.md)** · **[C++17 snippets](templates/cpp/sp-reference.hpp)**

Pattern recognition, arithmetic and number theory, combinatorics, geometry formulas, graph/DP/data-structure templates, contest pitfalls, and practice links to this archive. External references are cited in the full guide. Marked snippets generate the header with `python3 scripts/build_sp_reference.py`; their boundary and small-instance checks are part of the test suite.

## Create and run a problem with Make

Requires Make, Python 3.10+, and GCC with C++23 support for C++ problems. CPH is not required.

```bash
make new A_Line_Trip.cpp
make new B.py
# Edit the source and input.txt in practice/inbox/A_Line_Trip/.
make run A_Line_Trip.cpp
# Paste the expected answer into expected.txt, then:
make check A_Line_Trip.cpp
```

Each problem gets a folder containing its source, `input.txt`, `output.txt`, and `expected.txt`. The extension selects the language: `.cpp` for C++, `.py` for Python. Pass one filename per invocation. Creation refuses to overwrite an existing folder. Inputs and expected answers can be committed; generated `output.txt` is ignored. Starters handle one test case; uncomment the test-count read for problems that supply `t`. The previous `NAME=... LANG=...` syntax also works.

`make run` reads `input.txt`, writes and displays `output.txt`, and keeps stderr visible. Program execution has a five-second timeout; override it with `RUN_TIMEOUT=10` on `run` or `check`. Compilation is not timed. `make check` compares whitespace-separated tokens exactly; it does not implement floating-point tolerances or special judges. Use the existing interactive runner for interactive problems. New problems stay in the inbox until you explicitly file them:

```bash
make ingest          # Preview proposed classifications/moves
make ingest-apply    # Apply suggestions; samples stay in the problem folder
make lint
```

After filing, `make run A_Line_Trip.cpp` still finds the source through its catalog entry and uses the original sample folder. `make build A_Line_Trip.cpp` only compiles; `make help` lists commands. An explicit path also works, such as `make run solutions/strings/cf-stringtask.cpp`; cataloged inbox sources retain their original sample workspace. Other sources use input/output files alongside the source. The [workflow guide](notes/tooling/problem-workflow.md) covers header caching, flags, and archiving.

### Fast C++ headers

The new starter keeps `#include "bits/stdc++.h"`. Quoted includes search the source directory and configured include paths; they do not scan directories recursively. Make adds the repository include path and automatically builds/reuses a GCC precompiled header in ignored `build/pch/`. The first build costs extra; subsequent compilations can reuse the parsed standard headers. Unchanged programs also reuse their executable.

```bash
make pch                         # Optional: prepare the header before a contest
make run A_Line_Trip.cpp PCH=0   # Disable precompiled headers
make run A_Line_Trip.cpp CXX=clang++ PCH=0
make build A_Line_Trip.cpp CXXFLAGS='-std=c++23 -O0 -g -Wall -Wextra'
```

Compiler, flags, header contents, and dependency timestamps control cache reuse. Incompatible macros defined before the include can make GCC fall back to parsing the header; `-Winvalid-pch` reports this. Keep the include first, as in the starter. See GCC's [include search rules](https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html) and [precompiled-header requirements](https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html).

## Find a solution

All commands below run from the repository root and use Python 3.10 or newer. No Python packages are required.

```bash
python3 scripts/search.py "line trip"
python3 scripts/search.py --category dp
python3 scripts/search.py --tag sliding-window --language cpp
python3 scripts/search.py --category graphs
python3 scripts/search.py --platform codeforces --tag binary-search
python3 scripts/search.py A_Petya_and_Strings.cpp --paths
python3 scripts/search.py --list-categories
```

Search matches titles, filenames, original paths, known problem IDs, tags, and contest collections. Multiple query terms must all match. `--limit 20` shortens output; `--json` returns full metadata. Platform and problem ID filters work where that information is known.

Each implementation has one primary category and can have several tags. For example, a window problem can also appear under prefix sums or ordered sets in the tag index. C++ and Python implementations remain separate files, and original filenames are preserved.

## Layout

```text
solutions/        Problems grouped by their main pattern
  dynamic-programming/  Knapsack, intervals, sequences, Kadane, general
  graphs/               Traversal, shortest paths, spanning trees, DAG ordering
  data-structures/      DSU, range queries, ordered sets, heaps, stacks/queues
  math/                 Arithmetic, combinatorics, number theory
  binary-search/
  two-pointers-and-sliding-window/
  prefix-sums/
  greedy/
  ...
algorithms/       Standalone teaching/example implementations from sp/
templates/        C++ and Python submission starters
references/       Existing model solutions, kept separate from personal solutions
notes/            Canonical pattern notes and written explanations
practice/         Current scratch work and input/output
practice/legacy/  Preserved experiments, debug programs, and scratch sources
catalog/          Search metadata, generated indexes, and original move map
scripts/          Search, run, file a solution, and rebuild navigation
bits/, ext/       Existing local C++ headers, retained for include compatibility
build/            Ignored compiled files, including preserved legacy artifacts
archive/          Earlier planning reports, original tooling, and local CPH backups
```

## Run a solution

```bash
./run.sh A_Line_Trip.cpp
./run.sh solutions/strings/A_Petya_and_Strings.cpp
python3 scripts/run.py practice/legacy/main.py
```

On Windows, use `run.bat` or `python scripts/run.py`. C++ requires a compiler supporting C++23 (`g++` by default; override with `CXX`). The runner accepts a current path, an original path, or a unique filename. It compiles into `build/` with the repository root on the include path, so existing quoted local header includes still resolve.

Programs run with **practice/** as their working directory. Existing `input.txt`, `output.txt`, `myoutput.txt`, and `error.txt` were moved there. This supports solutions that open those relative filenames. Other problem-specific files should also be placed there. For a different working directory:

```bash
python3 scripts/run.py --cwd /path/to/data A_Line_Trip.cpp
```

Pass program arguments after `--`. VS Code's default build task runs the active source using this same runner.

Historical implementations are preserved as written: some are incomplete, experimental, or may not compile. Category labels do not imply an accepted submission.

## Self-organizing workflow

The agent follows [AGENTS.md](AGENTS.md): **INGEST → QUERY → LINT**. You can ask “organize my new solutions,” “find examples of prefix sum hashing,” or “check the repo.” It reads relevant implementations, preserves reviewed decisions, enriches existing pattern notes, and updates navigation and the log.

For direct use, put new attempts in `practice/inbox/` and run:

```bash
python3 scripts/ingest.py          # Preview proposed moves
python3 scripts/ingest.py --apply  # File sources and update navigation/log
python3 scripts/lint_repo.py      # Read-only health check
```

Ingestion also scans other non-legacy sources in `practice/`, stray root-level sources, and uncataloged files in the managed solution directories. Pass specific source paths to limit a run. It never automatically ingests `practice/legacy/`.

Basic ingestion uses local title/code signals and requires no API key. Its classifications remain suggestions. Agent-assisted ingestion adds code reading and explicit reviews; it runs when you request it. The hook performs structural checks at commit time; it does not run background ingestion.

The organizer skips unchanged source hashes. When a suggested implementation changes, it can update that suggestion and file location. When reviewed/locked code changes, it retains the classification and marks it for another review. A failed operation rolls back ordinary moves and metadata writes, and name collisions get distinct filenames so attempts are preserved.

`catalog/events.jsonl` records organization operations; [ORGANIZATION_LOG.md](ORGANIZATION_LOG.md) is the generated readable view. Dry runs and repeated ingestion with no changes do not create events. Classification and observation hashes describe current processing; `original_sha256` remains historical.

## Review and correct classifications

Use a current path, original path, or unique filename:

```bash
python3 scripts/review_solution.py A_Line_Trip.cpp \
  --category greedy \
  --evidence "Scans adjacent gaps and doubles the final return segment"
```

This previews the decision. Add `--apply` to save it. Use `--tags` for additional comma-separated categories and repeat `--pattern PATTERN_ID` to associate focused notes. Tags replace the old tag set; omitted pattern options preserve existing associations. Use `--clear-patterns` to remove them. Reviewed decisions are locked against automatic reclassification.

```bash
python3 scripts/search.py --changed
python3 scripts/search.py --needs-review
python3 scripts/search.py --suggested --limit 20
```

The [review queue](catalog/REVIEW.md) includes uncertain/empty implementations and changed source versions. A reviewed category never implies an accepted or correct submission.

## File a solution with a known category

```bash
python3 scripts/add_solution.py practice/inbox/new_problem.cpp \
  --category two-pointers-and-sliding-window \
  --tags prefix-sums \
  --title "My new problem"
```

Optional metadata: `--platform`, `--id`, and repeatable `--url`. Use `--role algorithm` for a teaching example or `--role reference` for a model solution. Explicitly supplied categories are recorded as reviewed and locked. Distinct attempts are retained if a filename is already in use.

## Learn and query patterns

The [pattern hub](notes/patterns/INDEX.md) explains recognition clues, invariants, pitfalls, and complexity. Each explanation links to your own examples; the catalog links back to the note.

```bash
python3 scripts/search.py --list-patterns
python3 scripts/search.py --pattern monotonic-deque
python3 scripts/search.py --notes "interval"
```

One canonical note per pattern lives under `notes/patterns/`. Its explanation is authored and preserved; only the marked examples block is generated. New associated solutions automatically appear on that page after ingestion/review. Agents should extend an existing explanation before creating another. Register a new note in `catalog/patterns.json` and include one `<!-- examples:start -->` / `<!-- examples:end -->` block.

`catalog/problems.json` remains the current catalog. Regenerate navigation after deliberate metadata or note changes:

```bash
python3 scripts/build_catalog.py
python3 scripts/lint_repo.py
```

## Automatic structural checks

The pre-commit hook is enabled for this checkout. In a fresh clone, enable it with:

```bash
python3 scripts/install_hooks.py
```

It checks a temporary copy of the **staged files**, so unstaged fixes cannot hide a broken commit. The hook never stages, rewrites, or commits anything. Structural failures block a commit. Pending inbox work and stale classifications are warnings; shared IDs and identical attempts are information. Use `python3 scripts/lint_repo.py --strict` to make warnings fail too.

Lint checks schema, source coverage, category locations, hashes, duplicate IDs/content, local Markdown links/anchors, pattern-note reachability, event records, and generated navigation. It does not execute historical submissions or infer judge verdicts. Commit source moves, catalog, scripts, and navigation together so staged checks see a consistent layout.

Tooling integration checks run with `python3 -m unittest discover -s tests -v`. They use temporary repositories and cover preservation, rollback, collisions, locked decisions, repeated ingestion, CPH samples, and staged checks.

## Migration record

`catalog/migration.json` records every original file's initial destination, original tracking state, and SHA-256 hash. All 1,497 original files passed the byte-preservation comparison after moving. Original configuration versions are saved under `archive/tooling/` before the editor and ignore settings were updated. Current paths are in `problems.json`; the migration manifest is a historical snapshot.

Existing CPH records were used where they supplied IDs and URLs. Original records and samples are preserved locally under ignored `archive/cph-original/`; matched records were also recreated beside their relocated sources with updated absolute paths and path hashes. Orphan records remain locally available. CPH and its backups are optional local data and are not needed to use the catalog or add solutions.

The migration preserved uncommitted source files and scratch input/output, retained compiled artifacts under ignored `build/legacy/`, and did not stage or commit changes. Earlier platform-based planning reports are archived under `archive/planning/`.

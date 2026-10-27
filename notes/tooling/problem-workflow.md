# Creating problems without CPH

## Start a problem

From the repository root:

```bash
make new A_Line_Trip.cpp
make new B.py
```

Use `.cpp` for C++ and `.py` for Python. Names before the extension use letters, digits, underscores and hyphens. `new` takes a filename, not a path, and creates the workspace itself. Pass one command and one filename per invocation. Make consumes the filename as an argument without requiring it to exist in the root directory.

The previous `make new NAME=A LANG=cpp`, `make run NAME=A`, and `SOURCE=...` forms still work. Do not mix a positional filename with `NAME=` or `SOURCE=`. With positional filenames, the extension selects the language regardless of `LANG`.

Creation refuses existing folders and never ingests sources automatically. It copies a minimal starter into:

```text
practice/inbox/A_Line_Trip/
  A_Line_Trip.cpp
  input.txt
  output.txt
  expected.txt
```

Edit the [C++ starter](../../templates/cpp/problem.cpp) or [Python starter](../../templates/python/problem.py) to customize future problems. Both default to one test case; the comments show where to read a test count. Input and expected answers are tracked normally; actual output is ignored. No CPH metadata is created or required.

## Browser imports with Competitive Companion

1. Install [Competitive Companion for Chrome](https://chromewebstore.google.com/detail/competitive-companion/cjnmckjndlpiamhfimnnjmnckgghkjbl).
2. Run `make companion` from this repository in an interactive terminal on the same Linux machine as Chrome.
3. Open a Codeforces or VJudge problem and wait for its statement and samples to load. Click the Companion extension icon. Both sites are listed in [Companion's supported websites](https://github.com/jmerle/competitive-companion#supported-websites); extraction is handled by the extension.
4. In the listening terminal, enter `cpp` (also `c++`) or `py` (also `python`), or `s` to skip. Each problem asks separately, including when importing a contest. An empty answer asks again.
5. Edit the created source. In another terminal at the repository root, run the printed `make run NAME.cpp` or `make check NAME.cpp` command (use `.py` for Python).

The receiver uses Python's standard library and listens only on `127.0.0.1:10043`. This is one of [Companion's default ports](https://github.com/jmerle/competitive-companion/blob/master/src/hosts/hosts.ts), so no port configuration is normally required. It acknowledges each request immediately and queues up to 100 problems while you choose languages. Browser success means queued; the terminal confirms actual creation. Ctrl-C stops the receiver and discards pending imports; click again to resend them. Created files remain.

If port 10043 is occupied, stop the other listener or run `python3 scripts/companion.py --port 10044` and add `10044` to **Custom ports** in Companion's extension options. Avoid running other Companion consumers unless you also want them to receive imports. If no prompt appears, check that the receiver is running, the extension is enabled, and the page has finished loading. Some VJudge statements have missing samples or require login; inspect the visible page and retry. This integration does not install or configure Chrome automatically.

Imported folders and sources use the problem title: `Y. Number of Ways` becomes `Number_of_Ways/Number_of_Ways.cpp`, and `k-th divisor` becomes `k-th_divisor/k-th_divisor.cpp`. Leading problem letters such as `Y.` are removed, whitespace and punctuation become underscores, and names are limited to 100 safe filename characters. Platform IDs and URLs stay in `problem.json`. Titles with no usable characters fall back to `problem`. Reimporting creates a separate `-attempt-2`, `-attempt-3`, etc. folder, preserving earlier source and samples. No source is compiled or executed during import, and nothing is classified, filed, staged, or committed.

One sample uses `input.txt`, `expected.txt`, and generated `output.txt`, matching manual creation. Multiple samples use:

```text
practice/inbox/Number_of_Ways/
  Number_of_Ways.cpp
  problem.json
  1.in
  1.expected.txt
  1.output.txt
  2.in
  2.expected.txt
  2.output.txt
```

`problem.json` preserves the received URL, title, constraints, flags, batch data, and original samples. Input/expected files preserve the sample text as UTF-8, including whitespace. Generated output files are ignored by Git. Each numbered `.in` file is a separate program invocation, in numeric order. `run` displays all outputs; `check` compares each against its matching `.expected.txt`, continues after failures, and returns failure if any sample fails. Compilation happens once. To add a custom sample, add the next numbered input and expected pair. If numbered inputs exist they take precedence over the single-sample files; keep one layout per workspace.

A sample block containing `t` stays one input file; individual cases inside it are not split. With no received samples, empty single-sample files are created and the terminal asks you to fill them. Samples do not include hidden judge tests. Interactive problems produce a terminal notice and need an interactive runner; floating-point tolerances and special judging remain outside token comparison. The extension owns website parsing, so site changes may require updating Companion.

## Run and compare

```bash
make run A_Line_Trip.cpp
make check A_Line_Trip.cpp
make run B.py
make build A_Line_Trip.cpp
```

`run` reads the whole `input.txt` through stdin, writes stdout to `output.txt`, and displays the result. Stderr stays on the terminal. The working directory is the sample folder, so relative file opens work there too. `check` runs the program and compares its output to `expected.txt`, ignoring whitespace differences. Nonzero program exits and mismatches fail the command. Fill `expected.txt` first: an empty expected file means you expect empty output. Floating-point answers require your own tolerance comparison; special judges need their own checker.

Program execution has a five-second timeout. For a slower solution, use `make run A_Line_Trip.cpp RUN_TIMEOUT=10` (also supported by `check`). The limit must be a finite positive number of seconds; it does not apply to compilation or PCH creation. On timeout the runner stops the program, reports the limit, retains any partial output, and exits with status 124 (Make reports the failed recipe).

`build` only compiles C++; Python has no compilation step. Bare filenames first select the corresponding inbox workspace, including its cataloged source after filing; otherwise they resolve an existing file or a unique catalog filename. Ambiguous catalog filenames require a path. Explicit paths also work, for example `make run solutions/strings/cf-stringtask.cpp`. Cataloged sources originally created in the inbox use their retained sample folder when available; other sources use their source folder. The older explicit `SOURCE=...` form continues to use the source folder directly. For interactive stdin, use `./run.sh path/to/file.cpp`; that existing runner still defaults to the top-level practice directory and supports `--cwd`.

## Manage and select samples

```bash
make samples Number_of_Ways.cpp
make check k-th_divisor.cpp SAMPLE=2
make run k-th_divisor.cpp SAMPLE=3
make sample-add Number_of_Ways.cpp INPUT=/tmp/custom.in EXPECTED=/tmp/custom.txt
```

`samples` lists each input/expected pair and reports missing files. `SAMPLE=N` selects the numbered input with that ID for `run`, `check`, or `debug`; a single `input.txt` is sample 1. Invalid or missing IDs fail before compilation.

`sample-add` reads an input and its expected answer from files, then appends a numbered pair. Paths are relative to the directory where Make runs (normally this repository root); quote paths containing spaces. Both `INPUT` and `EXPECTED` are required. It never runs the solution to invent an expected answer. If the workspace has one existing sample, it copies that pair to `1.in` and `1.expected.txt`, then adds your pair as sample 2. The original single-sample files remain unchanged; numbered inputs take precedence from then on. A fresh empty starter gets your pair as sample 1. Subsequent additions use the next unused number, preserving existing samples and outputs. Ordinary write failures roll back the files created by that addition.

These commands also work after ingestion, using the source's cataloged original sample workspace. The input/expected text is copied byte for byte. Generated actual outputs remain ignored by Git. `problem.json` stays the original import record; custom samples are represented by their files.

## Debug builds and colored stderr

```bash
make debug k-th_divisor.cpp
make debug k-th_divisor.cpp SAMPLE=2
make check k-th_divisor.cpp DEBUG=1
make run k-th_divisor.cpp DEBUG=1 SAMPLE=1
make build k-th_divisor.cpp DEBUG=1
```

`debug` runs and checks samples, enabling a C++ debug build. `DEBUG=1` enables the same build for `run`, `check`, or `build`. It appends `-O0 -g3 -Wall -Wextra -Wshadow`, AddressSanitizer and UndefinedBehaviorSanitizer, frame pointers, and libstdc++ assertions. Sanitizer findings fail the run. Debug mode defines `CP_DEBUG` and `LOCAL`, undefines `ONLINE_JUDGE`, and disables PCH. Debug executables have a separate cache under `build/problems/debug/`, preserving the normal executable cache. Custom compiler flags still apply; the debug flags are appended so debug optimization takes precedence. Use GCC or Clang with sanitizer support.

The [colored helper](../../templates/cpp/debugging.hpp) is adapted from the original [legacy helper](../../practice/legacy/debugging.cpp). The build injects it automatically, so no absolute include path needs to be pasted into your source. In a new C++ starter, write:

```cpp
int x = 7;
vector<int> values = {2, 4, 6};
debug(x, values);
int a[] = {1, 2, 3};
debugArr(a, 3);
```

The helper prints variable names, values, and source line numbers in color on stderr. Stderr stays visible in the terminal and is excluded from expected-output comparison. New starters define no-op `debug` and `debugArr` macros for ordinary builds and submissions; their arguments are not evaluated. Existing source bytes are preserved. For an older source, add the following fallback yourself if you want to leave debug calls in the source during normal builds:

```cpp
#ifndef CP_DEBUG
#define debug(...) ((void)0)
#define debugArr(...) ((void)0)
#endif
```

This fallback keeps submission code independent of repository headers. For Python, `debug` / `DEBUG=1` uses Python's development mode (`-X dev`) and checks the selected samples; C++ sanitizers and colored C++ macros do not apply.

## Imported metadata during ingestion

When a new source under `practice/inbox/NAME/` has an adjacent `problem.json`, ingestion reads its title, original URL, group, time/memory constraints, and interactive flag. Codeforces and VJudge URLs also populate recognized platform IDs; unknown platforms/IDs remain unknown. Leading problem labels such as `Y.` are removed from the catalog title. Explicit arguments to `add_solution.py` override imported values. Invalid metadata stops the operation before filing, rather than silently losing identity.

Constraints are stored as `time_limit_ms` and `memory_limit_mb`; they do not replace the local `RUN_TIMEOUT`. Imported groups become catalog collections. Metadata does not imply acceptance, correctness, difficulty, or a semantic classification. Implementation status remains unverified, and automatic categories remain suggestions. Existing catalog records are not silently overwritten when a sidecar changes.

## Header lookup and compilation speed

`#include "bits/stdc++.h"` remains the first include. Quoted includes search the source directory first and then the configured include paths. They do not recursively scan the repository. Make puts a cache directory and then the repository root on `-I` include paths, so the local header remains available from nested problem folders. A `bits/stdc++.h` beside the source can take precedence over the cache. See the [GCC include search documentation](https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html).

With GCC, Make copies the repository header into `build/pch/<configuration>/bits/stdc++.h` and compiles an adjacent `.gch`. GCC can load that precompiled header when processing the include. The first build takes extra time and disk space; later compilations can avoid reparsing those headers. Changes to source code still require compilation and linking. No timing guarantee applies to every compiler or problem.

```bash
make pch
make build A_Line_Trip.cpp CXXFLAGS='-std=c++23 -O0 -g -Wall -Wextra'
make run A_Line_Trip.cpp PCH=0
make run A_Line_Trip.cpp CXX=clang++ PCH=0
```

Defaults are `CXX=g++`, `CXXFLAGS='-std=c++23 -O2 -pipe'`, and `PCH=1`. Custom `CXXFLAGS` replace the entire default list; include your desired `-std=`. `CPPFLAGS` supplies extra preprocessing flags. Compiler identity, flags, repository header content, and dependency timestamps determine cache reuse. Executables are reused when their dependencies and configuration are unchanged. Failed compilations invalidate their saved build state. Delete the relevant ignored cache directory to force a rebuild; do not copy old `.gch` files into the source tree.

GCC requires compatible compiler binaries, flags, language and macro definitions. Keep the include before declarations and macro definitions; source-specific macros can invalidate the PCH. The builder enables `-Winvalid-pch` so GCC reports incompatible cached headers and can fall back to parsing. GCC supports one PCH per translation unit, so these commands precompile the standard aggregate header only; PBDS includes work through the normal include path. Other compilers require `PCH=0`. See [GCC's PCH rules](https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html).

## File completed attempts

```bash
make ingest
make ingest-apply
make lint
```

Ingestion uses the existing organizer. Automated categories remain suggestions; an agent can read the implementation and record a reviewed decision. The source moves to its category, while the input and expected-output files remain in the workspace. `make run problem.cpp` resolves the moved source through its original path in the catalog, retaining those samples. Do not rename or reuse that workspace name after filing. Alternate attempts need distinct names. A manually moved uncataloged source requires an explicit path. `make ingest`, `make ingest-apply`, `make lint`, and `make pch` continue to operate without a filename.

For an explicitly known category, use [the existing filing command](../../README.md#file-a-solution-with-a-known-category). No Make target stages, commits, pushes, or installs hooks.

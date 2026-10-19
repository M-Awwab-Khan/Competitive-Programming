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

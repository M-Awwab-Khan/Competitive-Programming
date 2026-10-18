# Practice workspace

Create an attempt from the repository root with `make new NAME=A LANG=cpp` (or `LANG=python`). This creates `inbox/A/A.cpp`, `input.txt`, `output.txt`, and `expected.txt`. Edit the source and input, then use `make run NAME=A`; use `make check NAME=A` after filling the expected answer. Pass the same language for Python runs. No CPH setup is needed.

Preview filing with `make ingest`; apply with `make ingest-apply`, or ask the agent to organize new solutions. Filing moves the source but leaves samples here; Make resolves the filed source using its original path in the catalog. Keep the sample folder name stable. See the [workflow guide](../notes/tooling/problem-workflow.md).

Source files and problem-folder input/expected files remain visible to Git; generated problem output and root-level text input/output files are ignored. The legacy runner uses this directory for relative file I/O; Make runs inside the selected problem folder. Existing experiments in `legacy/` are preserved and excluded from automatic ingestion.

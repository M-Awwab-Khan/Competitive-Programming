# Competitive programming archive agent

## Purpose

Keep this repository searchable by the patterns used in its actual implementations. Follow **INGEST → QUERY → LINT**, like the personal second-brain workflow. Read the implementation before making an explicit classification decision.

## Sources of truth

- `solutions/`, `algorithms/`, and `references/`: source implementations. Preserve every byte during organization. Alternate attempts remain separate.
- `catalog/problems.json`: current paths, categories, tags, pattern associations, classification evidence, and processed hashes.
- `catalog/patterns.json`: registered pattern notes. Each pattern has one canonical explanation under `notes/patterns/`.
- `catalog/events.jsonl`: append-only organization history; `ORGANIZATION_LOG.md` is its generated view.
- `catalog/migration.json` and `archive/`: historical records. Do not rewrite migration history when current paths change.
- `practice/inbox/` and other non-legacy sources in `practice/`: current attempts waiting to be filed. `practice/legacy/` is not an inbox.

Generated navigation: `catalog/INDEX.md`, `catalog/TAGS.md`, `catalog/REVIEW.md`, `catalog/stats.json`, `solutions/README.md`, `notes/INDEX.md`, `notes/patterns/INDEX.md`, `ORGANIZATION_LOG.md`, and marked example sections inside pattern notes. Regenerate them rather than editing generated content.

## INGEST

Triggered by “organize my new solutions,” “ingest the inbox,” or an equivalent request.

1. Run `python3 scripts/ingest.py` to preview new/changed sources. Inspect the proposed moves and source code; skip unchanged hashes.
2. Read each new or changed implementation. Distinguish the approach actually written from techniques suggested by the title or comments. Shared template helpers and commented-out algorithms are not classification evidence.
3. Preserve manually reviewed or locked classifications. If the implementation changed, keep the label and flag it for review until an explicit new decision is supported by the code.
4. Apply the authorized ingestion with `python3 scripts/ingest.py --apply`. Automated labels remain suggestions; uncertain or empty files go to `needs-review`.
5. To record a decision after reading the code, use `python3 scripts/review_solution.py FILE --category CATEGORY --tags TAGS --evidence "Implementation-specific reason" --apply`. Do not ask for approval for routine reversible filing already authorized by the user.
6. Preserve unknown platform/ID/verdict fields. CPH is an optional local clue, never a dependency. A reviewed category does not mean the solution was accepted or is correct.
7. Search existing pattern notes first. Extend a matching note if the source teaches a new invariant or pitfall; do not create a second explanation of the same idea. Associate examples using `--pattern PATTERN_ID`. Register genuinely new notes in `catalog/patterns.json` and keep one marked examples block.
8. Run LINT. Summarize additions, changed classifications, and unresolved cases. Do not stage or commit unless explicitly requested.

Use `scripts/add_solution.py` when the category is already known. The shared organizer updates navigation and logs as one operation and rolls back on ordinary failures. Never silently overwrite a source or merge away an attempt.

## QUERY

Triggered by requests to find examples, explain an approach, compare patterns, or plan revision.

1. Search with `scripts/search.py`; use `--category`, `--tag`, `--pattern`, `--platform`, `--language`, and `--changed` as useful. Read `notes/INDEX.md` for explanations.
2. Read relevant implementation bodies and pattern notes. Answer with links to the actual files, the invariant/decision that identifies the pattern, and any visible implementation limitations.
3. If the requested example is not present, say so. Never invent acceptance, difficulty, complexity, solve dates, or personal learning history.
4. Prefer enriching one canonical note over repeating an explanation in many per-problem files.

## LINT

Run `python3 scripts/lint_repo.py` after every ingest/review or on request. This is read-only and checks:

- catalog schema, unique keys/paths, known categories/tags/pattern IDs, and physical category consistency;
- uncataloged or missing sources and unprocessed inbox files;
- modified source hashes, including locked decisions needing another review;
- duplicate problem IDs and exact content (report alternate attempts; do not delete them);
- broken local Markdown links/anchors and missing/unindexed pattern notes;
- generated navigation consistency and organization log validity.

For stale generated navigation, run `python3 scripts/build_catalog.py` and lint again. Structural errors fail the command; duplicate attempts, pending inbox sources, and stale classifications are reported separately as warnings/information. The pre-commit hook checks a temporary snapshot of the staged files and never stages or rewrites anything.

## Classifications and pattern notes

- Existing category names are in `catalog/problems.json`; focused patterns are in `catalog/patterns.json`. Reuse these names where they fit.
- `classification_sha256` binds a decision to the code that was classified; `observed_sha256` tracks the last ingested bytes. `original_sha256` is historical and must remain unchanged.
- `classification_locked: true` and `reviewed` decisions survive automatic ingestion. A source change can set `review_required` without overwriting that decision.
- Keep submission/implementation status separate from classification confidence.
- Pattern notes should include recognition clues, invariant or recurrence, complexity with assumptions, common mistakes, related patterns, and links to local examples. Generated examples are suggestions unless their classification has been reviewed.

## Operational rules

Use the existing standard-library scripts. Do not require a hosted LLM/API key for basic organization. Read-only checks and automatic hooks do not make semantic decisions or move files; an agent invoked by the user can read code, file sources, and improve notes.

Do not execute historical submissions merely to classify them. Do not modify `.git/`, `.obsidian/`, or other repositories for this task. Hook installation is an explicit local setup command documented in README; user authorization to set it up permits the required Git configuration.

If `catalog/.organize-journal.json` exists after an interrupted operation, inspect its paths and event against the catalog and filesystem before changing files. Preserve source files, recover inconsistent moves/metadata, regenerate navigation, and lint. Do not simply discard an unresolved journal. A stale lock may be removed only after confirming no organizer is running and the journal has been resolved.

#!/usr/bin/env python3
"""Create a local inventory and proposed migration map; never move source files."""
import argparse
import csv
import hashlib
import json
import re
import subprocess
import unicodedata
from collections import Counter, defaultdict
from pathlib import Path
from urllib.parse import parse_qs, urlparse

ROOT = Path(__file__).resolve().parents[1]
GENERATED = {"scripts/preview_organization.py", "catalog/inventory.json",
             "catalog/migration.csv", "catalog/MIGRATION_PREVIEW.md"}

def slug(value):
    text = unicodedata.normalize("NFKD", value).encode("ascii", "ignore").decode().lower()
    return re.sub(r"[^a-z0-9]+", "-", text).strip("-") or "untitled"

def identify(url):
    u = urlparse(url)
    host, path = u.netloc.removeprefix("www."), u.path
    if host == "codeforces.com":
        m = re.search(r"/(?:problemset/problem|contest)/(\d+)/(?:problem/)?([A-Za-z0-9]+)$", path)
        if m:
            return "codeforces", m[1] + m[2].upper()
        m = re.search(r"/gym/(\d+)/problem/([A-Za-z0-9]+)$", path)
        if m:
            return "codeforces", "gym-" + m[1] + "-" + m[2].upper()
    if host == "atcoder.jp":
        m = re.search(r"/contests/([^/]+)/tasks/([^/]+)", path)
        if m:
            return "atcoder", m[2]
    if host == "vjudge.net":
        m = re.search(r"/problem/([^-]+)-(.+)$", path)
        platforms = {"codeforces": "codeforces", "uva": "uva", "kattis": "kattis",
                     "spoj": "spoj", "atcoder": "atcoder", "cses": "cses",
                     "codechef": "codechef", "yosupo": "library-checker"}
        if m:
            return platforms.get(m[1].lower(), slug(m[1])), m[2]
        m = re.search(r"/contest/(\d+)$", path)
        if m and u.fragment.startswith("problem/"):
            return "vjudge", "contest-" + m[1] + "-" + u.fragment.split("/")[-1]
    if host == "usaco.org":
        ids = parse_qs(u.query).get("cpid")
        if ids:
            return "usaco", "cpid-" + ids[0]
    if host == "onlinejudge.org":
        ids = parse_qs(u.query).get("problem")
        if ids:
            return "uva", "oj-internal-" + ids[0]
    for domain, platform, pattern in [
        ("open.kattis.com", "kattis", r"/problems/([^/]+)"),
        ("spoj.com", "spoj", r"/problems/([^/]+)"),
        ("codechef.com", "codechef", r"/problems/([^/]+)"),
        ("judge.yosupo.jp", "library-checker", r"/problem/([^/]+)"),
        ("cses.fi", "cses", r"/problemset/task/(\d+)"),
    ]:
        if host == domain:
            m = re.search(pattern, path)
            if m:
                return platform, m[1]
    return None, None

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path, default=ROOT / "catalog")
    args = parser.parse_args()
    output = args.output_dir.resolve()
    tracked = set(subprocess.check_output(["git", "ls-files", "-z"], cwd=ROOT).decode().split("\0"))
    files = sorted(p for p in ROOT.rglob("*")
                   if p.is_file() and ".git" not in p.relative_to(ROOT).parts
                   and p.relative_to(ROOT).as_posix() not in GENERATED
                   and not p.is_relative_to(output))
    by_name = defaultdict(list)
    for p in files:
        by_name[p.name].append(p.relative_to(ROOT).as_posix())
    metadata, malformed, orphaned = defaultdict(list), [], []
    for p in files:
        if p.suffix != ".prob":
            continue
        rel = p.relative_to(ROOT).as_posix()
        try:
            obj = json.loads(p.read_text())
            src = Path(obj.get("srcPath", ""))
            if src.is_absolute():
                try:
                    key = src.relative_to(ROOT).as_posix()
                except ValueError:
                    key = None
            else:
                key = src.as_posix()
            match = "exact-path"
            if key not in {f.relative_to(ROOT).as_posix() for f in files}:
                matches = by_name[src.name]
                key = matches[0] if len(matches) == 1 else None
                match = "unique-basename"
            if not key:
                orphaned.append(rel)
                continue
            metadata[key].append({"record": rel, "match": match,
                                  "name": obj.get("name"), "url": obj.get("url"),
                                  "group": obj.get("group"),
                                  "sample_count": len(obj.get("tests", []))})
        except (ValueError, TypeError, OSError):
            malformed.append(rel)
    rows = []
    prefixes = {"cf": "codeforces", "cses": "cses", "kattis": "kattis", "uva": "uva",
                "usaco": "usaco", "spoj": "spoj", "codechef": "codechef",
                "at": "atcoder", "atcoder": "atcoder", "hr": "hackerrank",
                "hackerrank": "hackerrank", "tlx": "tlx", "troc": "tlx",
                "yuki": "yukicoder", "qoj": "qoj"}
    for p in files:
        rel = p.relative_to(ROOT).as_posix()
        data = p.read_bytes()
        records = metadata.get(rel, [])
        identities = {identify(r.get("url") or "") for r in records}
        identities.discard((None, None))
        platform, problem_id = next(iter(identities)) if len(identities) == 1 else (None, None)
        category, action, confidence, reason, dest = "support", "keep", "high", "Existing configuration or support file", rel
        title = next((r["name"] for r in records if r.get("name") and not r["name"].startswith("Local:")), p.stem)
        if ".cph" in p.parts:
            category, action, reason = "cph-metadata", "update-association", "Preserve samples; update srcPath and CPH association when source moves"
        elif p.parts[-1].startswith(".") or rel.startswith(".vscode/"):
            pass
        elif p.suffix in {".gch", ".exe", ".out", ".bin"} or data.startswith(b"\x7fELF"):
            category, action, reason = "build-artifact", "review", "Preserve during migration; later exclude compiler output from version control"
            dest = "build/legacy/" + rel
        elif rel.startswith(("bits/", "ext/")):
            category, action, confidence, reason = "local-toolchain", "review", "medium", "Check compiler include paths before relocation"
        elif p.name in {"cp-template.cpp", "py-template.py"}:
            category, action, reason = "template", "move", "Submission template"
            dest = "templates/" + ("cpp/" if p.suffix == ".cpp" else "python/") + p.name
        elif rel.startswith("model-solutions/"):
            category, action, reason = "reference", "move", "Existing reference collection"
            dest = "references/" + rel
        elif p.name == "Diophantine_equations.md":
            category, action, reason, dest = "notes", "move", "Mathematics notes", "notes/math/diophantine-equations.md"
        elif p.name in {"run.sh", "run.bat", "scrape_suspicious_submissions.py"}:
            category, action, confidence, reason = "tooling", "review", "medium", "Review working-directory and relative-path assumptions"
            dest = "scripts/" + p.name
        elif p.name in {"main.cpp", "main.py", "temp.cpp", "a.cpp", "check.cpp", "contest.cpp",
                         "test_brightness.cpp", "testing_bigint.cpp", "testing_debug.cpp", "debugging.cpp",
                         "version.cpp", "input.txt", "output.txt", "error.txt", "myoutput.txt"} or p.suffix == ".cppi":
            category, action, confidence, reason = "practice-candidate", "review", "low", "Possible scratch work; inspect before classifying"
            dest = "practice/legacy/" + rel
        elif p.suffix in {".cpp", ".py"}:
            category, action = "solution", "move"
            if platform:
                confidence, reason = "high", "Problem identity from associated CPH URL"
                if platform == "vjudge":
                    reason += "; original judge unresolved"
                if len(records) > 1 or any(r["match"] != "exact-path" for r in records):
                    action = "review"
            else:
                prefix = re.split(r"[-_]", p.stem.lower())[0]
                platform = prefixes.get(prefix)
                confidence = "medium" if platform else "low"
                reason = "Platform prefix only; problem ID unresolved" if platform else "Origin unresolved; preserve original filename"
                action = "review"
            if len(identities) > 1:
                platform, problem_id, confidence, action, reason = None, None, "low", "review", "Conflicting CPH identities"
            if problem_id:
                clean_title = re.sub(r"^(?:[A-Z]+\d*|Problem\s+\d+)\s*[.:-]\s*", "", title)
                folder = slug(problem_id) + "-" + slug(clean_title)
                dest = "solutions/" + platform + "/" + folder + "/solution" + p.suffix
            else:
                dest = "solutions/" + (platform or "unidentified") + "/" + p.name
        rows.append(dict(source=rel, proposed_destination=dest, category=category, action=action,
                         confidence=confidence, reason=reason, platform=platform, problem_id=problem_id,
                         title=title, tracked=rel in tracked, size_bytes=len(data),
                         sha256=hashlib.sha256(data).hexdigest(), metadata=records))
    destinations = defaultdict(list)
    hashes = defaultdict(list)
    for row in rows:
        destinations[row["proposed_destination"]].append(row)
        hashes[row["sha256"]].append(row["source"])
    collisions = []
    for dest, group in destinations.items():
        if len(group) < 2:
            continue
        collisions.append({"destination": dest, "sources": [r["source"] for r in group]})
        for row in group:
            target = Path(dest)
            suffix = hashlib.sha256(row["source"].encode()).hexdigest()[:8]
            row["proposed_destination"] = str(target.with_name("variant-" + slug(Path(row["source"]).stem) + "-" + suffix + target.suffix))
            row["action"] = "review"
            row["reason"] += "; shared destination, preserve as separate variant"
    duplicates = [paths for paths in hashes.values() if len(paths) > 1]
    summary = dict(total_files=len(rows), total_bytes=sum(r["size_bytes"] for r in rows),
                   source_files=sum(Path(r["source"]).suffix in {".cpp", ".py"} for r in rows),
                   categories=dict(Counter(r["category"] for r in rows)),
                   actions=dict(Counter(r["action"] for r in rows)),
                   confidence=dict(Counter(r["confidence"] for r in rows)),
                   solution_platforms=dict(Counter(r["platform"] or "unidentified" for r in rows if r["category"] == "solution")),
                   solutions_with_problem_id=sum(r["category"] == "solution" and bool(r["problem_id"]) for r in rows),
                   destination_collisions=len(collisions), duplicate_content_groups=len(duplicates),
                   orphaned_cph_records=len(orphaned), malformed_cph_records=len(malformed))
    assert len({r["source"] for r in rows}) == len(rows)
    assert len({r["proposed_destination"] for r in rows}) == len(rows)
    payload = dict(schema_version=1, root=str(ROOT), scope="Local snapshot excluding .git and generated organization reports; includes ignored files",
                   summary=summary, files=rows, destination_collisions=collisions,
                   duplicate_content_groups=duplicates, orphaned_cph_records=orphaned, malformed_cph_records=malformed)
    output.mkdir(parents=True, exist_ok=True)
    (output / "inventory.json").write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n")
    fields = ["source", "proposed_destination", "category", "action", "confidence", "platform", "problem_id", "title", "tracked", "size_bytes", "sha256", "reason"]
    with (output / "migration.csv").open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(rows)
    lines = ["# Repository organization preview", "",
             "This is a proposal. No original files have been moved, edited, or deleted.",
             "Regenerate with: python3 scripts/preview_organization.py", "",
             "The inventory includes tracked, untracked, and ignored files, excluding .git and these generated reports.",
             "It records file hashes, original paths, CPH associations, and proposed destinations.",
             "Classification uses local metadata and explicit filename prefixes. IDs, topics, acceptance status, and original judges are not guessed.", "",
             "## Snapshot", "", "| Measure | Count |", "| --- | ---: |"]
    lines += ["| " + k.replace("_", " ") + " | " + str(v) + " |" for k,v in summary.items() if not isinstance(v, dict)]
    lines += ["", "## Solution platforms", "", "| Platform | Files |", "| --- | ---: |"]
    lines += [f"| {k} | {v} |" for k,v in sorted(summary["solution_platforms"].items())]
    lines += ["", "## Before applying moves", "",
              "- Preserve all current working-tree changes and untracked files; do not stage or commit them automatically.",
              "- Back up ignored CPH records and local samples, which Git does not currently preserve.",
              "- Review every row marked review in migration.csv, including unresolved origins and alternate implementations.",
              "- Keep VJudge contest identities when the original judge is unknown. UVa oj-internal IDs are website keys, not UVa problem numbers.",
              "- Move solutions without editing code, preserving separate variants and recording old-to-new paths.",
              "- Update CPH srcPath and filename/path associations using a CPH-compatible migration, and check sample discovery.",
              "- Inspect run.sh/run.bat working-directory assumptions and relative file I/O before relocating them.",
              "- Replace the Windows-specific editor compiler path as appropriate; send future build output to build/.",
              "- Inspect bits/ and ext/ local headers and compiler include paths before changing their locations.",
              "- Compare original file hashes and counts after migration. Keep artifacts until cleanup is explicitly reviewed.",
              "- Build the final problem catalog and title/platform/topic search after identities and paths are settled.", "",
              "## Classification limits", "",
              "Generic names and A_/B_/C_ prefixes do not establish a platform. They remain unidentified.",
              "Algorithm-like filenames and sp/ files remain solution candidates until their purpose is reviewed.",
              "Filename prefix matches identify a likely platform only; they do not establish a problem ID.",
              "Multiple implementations can belong to one problem. Shared destinations receive unique variant names; nothing is deduplicated.",
              "Exact duplicate hashes are reported for review, including empty or generated files.",
              "No external judge lookups were performed.", "",
              "## Destination collisions", ""]
    for item in collisions:
        lines.append("- " + item["destination"] + ": " + ", ".join(item["sources"]))
    if not collisions:
        lines.append("None.")
    lines += ["", "## Metadata needing attention", ""]
    lines += ["- Orphaned: " + p for p in orphaned]
    lines += ["- Malformed: " + p for p in malformed]
    if not orphaned and not malformed:
        lines.append("None.")
    lines += ["", "## Files", "",
              "- [Complete inventory with hashes and metadata](inventory.json)",
              "- [Full proposed move map](migration.csv)", ""]
    (output / "MIGRATION_PREVIEW.md").write_text("\n".join(lines))
    print(json.dumps(summary, indent=2))

if __name__ == "__main__":
    main()

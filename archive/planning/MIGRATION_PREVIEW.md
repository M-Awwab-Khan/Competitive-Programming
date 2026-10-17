# Repository organization preview

This is a proposal. No original files have been moved, edited, or deleted.
Regenerate with: python3 scripts/preview_organization.py

The inventory includes tracked, untracked, and ignored files, excluding .git and these generated reports.
It records file hashes, original paths, CPH associations, and proposed destinations.
Classification uses local metadata and explicit filename prefixes. IDs, topics, acceptance status, and original judges are not guessed.

## Snapshot

| Measure | Count |
| --- | ---: |
| total files | 1497 |
| total bytes | 276540507 |
| source files | 1049 |
| solutions with problem id | 352 |
| destination collisions | 0 |
| duplicate content groups | 3 |
| orphaned cph records | 37 |
| malformed cph records | 0 |

## Solution platforms

| Platform | Files |
| --- | ---: |
| atcoder | 45 |
| codechef | 2 |
| codeforces | 238 |
| cses | 37 |
| eolymp | 2 |
| gym | 2 |
| hackerrank | 2 |
| kattis | 39 |
| library-checker | 1 |
| spoj | 3 |
| tlx | 4 |
| unidentified | 480 |
| usaco | 39 |
| uva | 34 |
| vjudge | 103 |
| yukicoder | 2 |

## Before applying moves

- Preserve all current working-tree changes and untracked files; do not stage or commit them automatically.
- Back up ignored CPH records and local samples, which Git does not currently preserve.
- Review every row marked review in migration.csv, including unresolved origins and alternate implementations.
- Keep VJudge contest identities when the original judge is unknown. UVa oj-internal IDs are website keys, not UVa problem numbers.
- Move solutions without editing code, preserving separate variants and recording old-to-new paths.
- Update CPH srcPath and filename/path associations using a CPH-compatible migration, and check sample discovery.
- Inspect run.sh/run.bat working-directory assumptions and relative file I/O before relocating them.
- Replace the Windows-specific editor compiler path as appropriate; send future build output to build/.
- Inspect bits/ and ext/ local headers and compiler include paths before changing their locations.
- Compare original file hashes and counts after migration. Keep artifacts until cleanup is explicitly reviewed.
- Build the final problem catalog and title/platform/topic search after identities and paths are settled.

## Classification limits

Generic names and A_/B_/C_ prefixes do not establish a platform. They remain unidentified.
Algorithm-like filenames and sp/ files remain solution candidates until their purpose is reviewed.
Filename prefix matches identify a likely platform only; they do not establish a problem ID.
Multiple implementations can belong to one problem. Shared destinations receive unique variant names; nothing is deduplicated.
Exact duplicate hashes are reported for review, including empty or generated files.
No external judge lookups were performed.

## Destination collisions

None.

## Metadata needing attention

- Orphaned: .cph/.10978_Let_s_Play_Magic.cpp_bdc4fb8dda19b7887663e2aad8bba5e5.prob
- Orphaned: .cph/.AX_Permutation_Game.cpp_a22062bdaad125dc26e332d5a86425c5.prob
- Orphaned: .cph/.A_Math_Problem.cpp_f6847d0e172d24157181ff88d0398501.prob
- Orphaned: .cph/.A_Square_sorted.cpp_3b0642d32f701b12851cd7f92e890a1e.prob
- Orphaned: .cph/.A_Walking_on_the_Safe_Side.java_5378bc1529c73ac234175d0af7c1b73f.prob
- Orphaned: .cph/.Air_Cownditioning.cpp_300ef20e2480a142cfaf4a893051d851.prob
- Orphaned: .cph/.B_Points_on_Plane.java_8d7657edf4dc6c58445d0958571f4e5f.prob
- Orphaned: .cph/.B_Variety_is_Discouraged.java_65683c19b6a012f44f8bc13090524b94.prob
- Orphaned: .cph/.B_Vera_And_LCS.cpp_6a452314da7b403c3c422cc6d59f67da.prob
- Orphaned: .cph/.C_Alternative_Thinking.cpp_132aadf7ff18c647bd7d2ef3ee734c2e.prob
- Orphaned: .cph/.C_Good_Subarrays.cpp_a4893368987764b8a8d235c30343b7df.prob
- Orphaned: .cph/.C_Increase_and_Copy.java_315ac27a48562d3e6df5d6257ce275a2.prob
- Orphaned: .cph/.D_Circle_Lattice_Points.cpp_994d416d7e400279080ba0f180e85758.prob
- Orphaned: .cph/.E_Divisibility.cpp_d2b5c94be977b14f3c744b3a542e8a95.prob
- Orphaned: .cph/.E_Fun_Sum.cpp_34fbdd99ea099f32f51dfaf8ed384cd3.prob
- Orphaned: .cph/.G_Pesky_Mosquitoes.cpp_a28bd3011bd54737110a2a7f7e5f611d.prob
- Orphaned: .cph/.H_Mixing_MEXes.cpp_1c93418ef36e0d183fc1ec86c78944c6.prob
- Orphaned: .cph/.Only_I_did_it.py_854708c2e7a87cfa7455ad89d5780e2e.prob
- Orphaned: .cph/.Problem_1_Cow_College.cpp_22d08b7c97be7519ce8676d4f7ba4107.prob
- Orphaned: .cph/.Problem_1_Cow_Gymnastics.cpp_fafc2d027b7b68d833ff5ce4320adb7e.prob
- Orphaned: .cph/.Problem_1_Don_t_Be_Last.cpp_57fb0b8c5b2a9e4fae07667f86667d95.prob
- Orphaned: .cph/.Problem_1_Photoshoot.cpp_3173746e753e9122f972f7e06f69e9f9.prob
- Orphaned: .cph/.Problem_1_Sleeping_in_Class.cpp_0de721498689d8071512d6e7fa2725b2.prob
- Orphaned: .cph/.Problem_2_Air_Cownditioning_II.cpp_c87af19d8b06429a49cd529268333760.prob
- Orphaned: .cph/.Problem_2_Angry_Cows.cpp_7089ccab7d48c41668870d59f11d06be.prob
- Orphaned: .cph/.Problem_2_Bovine_Genomics.cpp_fa4cf91dbefd6630d4cc25761bbddec3.prob
- Orphaned: .cph/.Problem_2_Cities_and_States.py_52f2a3b368f49f27e0192e308510eaa7.prob
- Orphaned: .cph/.Problem_2_Mad_Scientist.cpp_7cb231cddccca9c19e61e8ba754c01a7.prob
- Orphaned: .cph/.Problem_2_Sleepy_Cow_Sorting.cpp_56e02b172fdcfb06c4957b3d339ab9f0.prob
- Orphaned: .cph/.Problem_2_Why_Did_the_Cow_Cross_the_Road_II.py_94c680f7e9b6414fdc3ec135beb81bcd.prob
- Orphaned: .cph/.Problem_3_Livestock_Lineup.cpp_e15b19e24cca8aa52cd1d28ea2aa8ce3.prob
- Orphaned: .cph/.Problem_3_Race.cpp_4b2558ff5a36c5c59c2bab85dc386db4.prob
- Orphaned: .cph/.Problem_3_The_Cow_Signal.cpp_ea8955322556f1a706622fff95db3990.prob
- Orphaned: .cph/.Problem_3_Watching_Mooloo.cpp_08582e1a1d3fe56922804b802140085a.prob
- Orphaned: .cph/.Problem_3_Why_Did_the_Cow_Cross_the_Road_III.cpp_81c8d1e761e7d6782fbcbf832122c865.prob
- Orphaned: .cph/.Y_Grid_2.cpp_243e2a40ddbb235d62e65d9969523f5e.prob
- Orphaned: .cph/.コンテスト.cpp_4b2ce129ec132c16568196c5d6fb62ac.prob

## Files

- [Complete inventory with hashes and metadata](inventory.json)
- [Full proposed move map](migration.csv)

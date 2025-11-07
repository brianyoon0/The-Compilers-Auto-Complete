## Quick orientation for AI coding agents

This repository is a small C++17 project using CMake that implements an autocomplete engine (Trie and TST). The goal of these instructions is to point an AI agent to the precise files, patterns, and commands needed to be immediately productive.

- Project root: contains `CMakeLists.txt` (build rules) and `README.md` (course/project instructions).
- Entry point: `src/main.cpp` — simple CLI entry; update this to change runtime behavior.
- Core modules:
  - `include/Trie.h` and `src/Trie.cpp` — Trie interface and implementation (insert, search, getSuggestions).
  - `include/TST.h` and `src/TST.cpp` — Ternary Search Tree implementation (alternate autocomplete structure).
- Data and resources: `data/` (word lists or dictionaries) and `resources/` (docs/images). Look here for sample inputs.

Key conventions and patterns
- CMake: headers are included via `include_directories(include)` and source/header files are explicitly listed in `add_executable(...)`. When adding new source or header files, update `CMakeLists.txt`.
- API surfaces: public APIs live in `include/*.h` and implementations in `src/*.cpp`. Typical pattern: header declares class (e.g., `class Trie`) and src implements methods.
- Memory: current `TrieNode` uses raw pointers in `include/Trie.h`; destructor/cleanup logic lives in `Trie`'s implementation — be careful to preserve ownership semantics and avoid leaks when editing.

Build and run (Windows PowerShell examples)
- Out-of-source build (recommended):
  - mkdir build; cmake -S . -B build
  - cmake --build build --config Release
  - Executable location depends on generator; often `build\The-Compilers.exe` or `build\Release\The-Compilers.exe`.
- Quick single-folder variant:
  - mkdir build; cd build; cmake ..; cmake --build . --config Release

Debugging and testing notes
- There are no unit tests present. To test behavior, modify `src/main.cpp` to exercise your new functions, then build and run the binary.
- For interactive debugging in VS Code, open the folder, configure the C++ extension and CMake Tools (or generate a Debug build with `cmake --build build --config Debug`) and launch the produced exe.

Editing guidance and common tasks
- Add a new data structure: put public declarations in `include/`, implementations in `src/`, and add both files to `CMakeLists.txt` under `add_executable`.
- When changing class APIs (header), update all call sites — common call sites are `src/main.cpp` and tests/examples that may be placed in `data/` or `resources/`.
- Keep method names and signatures consistent with existing patterns: e.g., `Trie` exposes `insert(const std::string&)`, `bool search(const std::string&) const`, `std::vector<std::string> getSuggestions(const std::string&) const`.

Integration points worth checking
- `include/Trie.h` documents the public contract for the Trie; implementations must manage `TrieNode*` lifecycle (see `clear` helper pattern in the header).
- `src/TST.cpp` provides an alternative autocomplete engine — compare performance and API surface when implementing features.

When in doubt
- Prefer minimal, local edits and run the build to verify no compile errors. The CMake target name is `The-Compilers` (hyphen in target name), and the executable name is listed in `CMakeLists.txt`.
- If you need runtime sample input, inspect `data/` for dictionaries or example files; otherwise, add a small test harness in `src/main.cpp`.

If you want me to expand any section (examples of common edits, a small test harness, or CI/cmake improvements), tell me which area and I will add a focused PR.

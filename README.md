# Autocomplete Engine: Trie vs TST

A performance comparison tool for autocomplete functionality using two different data structures: **Trie** (Prefix Tree) and **Ternary Search Tree (TST)**.

## Description

This project implements and benchmarks two popular data structures for autocomplete systems:

- **Trie (Prefix Tree)**: A tree-like data structure where each node represents a character, optimized for fast prefix lookups
- **TST (Ternary Search Tree)**: A space-efficient alternative that combines properties of binary search trees and tries

The program loads a dictionary of words, builds both data structures, and allows you to interactively query them while measuring their performance characteristics including:
- Build time (milliseconds)
- Memory usage (megabytes)
- Query time (microseconds)

## How to run the code

We opted in using `Clion` due to running into some linking issues with `VScode`

### Instructions

1. Open CLion and select `File → Open`
2. Navigate to and select the `The-Compilers-Auto-Complete` folder
3. CLion will automatically detect the CMakeLists.txt and configure the project
4. Click the green play button or press `Shift+F10` to build and run

### Setting up the Dictionary
You may either use our list of words found in `include/words.txt` or you may create your own by: 
1. Create a `data` folder in the project root if it doesn't exist
2. Add a `words.txt` file containing one word per line
3. Example `words.txt`:
```
   apple
   application
   apply
   banana
   band
```

### Usage

1. Run the program
2. Wait for both data structures to build (timing will be displayed)
3. Enter a prefix when prompted (e.g., "app" to find "apple", "application", etc.)
4. View the top 10 suggestions from both Trie and TST
5. Compare the query times (displayed in microseconds)
6. Type `exit` to quit

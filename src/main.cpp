#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <iomanip> // For formatting output

// Include your headers (assuming they are in the 'include' path)
#include "Trie.H" 
#include "TST.h"  

using namespace std;
using namespace std::chrono;

// Helper function to lowercase strings
static string lower(string s) {
    for (char &c : s)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

// Helper to print the top 10 results in the desired format
void printSuggestions(const vector<string>& results) {
    if (results.empty()) {
        cout << "  (No suggestions found)\n";
        return;
    }

    int count = 0;
    for (const auto& res : results) {
        if (count >= 10) break; // Only print top 10
        count++;
        
        // Print: " 1. result"
        cout << " " << setw(2) << count << ". " << res;

        // Formatting for 4 columns
        if (count % 4 == 0) {
            cout << "\n";
        } else {
            cout << "\t"; // Use tab for spacing
        }
    }
    if (count % 4 != 0) {
        cout << "\n"; // Add a final newline if we didn't end on a multiple of 4
    }
}


int main() {
    // --- 1. Load Words from File ---
    
    // Use a relative path. Run your executable from the project's root directory.
    string filepath = "./data/words.txt"; 
    ifstream fin(filepath);
    if (!fin.is_open()) {
        cerr << "Error: could not open file: " << filepath << "\n";
        cerr << "Please run this executable from the project's root directory.\n";
        return 1;
    }

    vector<string> words;
    string line;
    while (getline(fin, line)) {
        line = lower(line);
        if (!line.empty()) words.push_back(line);
    }
    fin.close();

    cout << "Autocomplete Engine: Trie vs Ternary\n";
    cout << "Building data structures ... ";
    cout.flush(); // Force print before long build

    // --- 2. Build and Time Trie ---
    Trie trie;
    auto trie_start = high_resolution_clock::now();
    for (const auto &w : words) {
        trie.insert(w);
    }
    auto trie_end = high_resolution_clock::now();
    auto trie_build_time = duration_cast<milliseconds>(trie_end - trie_start).count();
    
    // Note: This is a rough approximation. It doesn't account for
    // the overhead of the unordered_map's internal allocations.
    double trie_memory_mb = (trie.getNodeCount() * sizeof(TrieNode)) / 1'048'576.0; // 1024*1024

    
    // --- 3. Build and Time TST ---
    // (Assuming TST has getNodeCount() and TSTNode is defined in TST.h)
    TST tst;
    auto tst_start = high_resolution_clock::now();
    for (const auto &w : words) {
        tst.insert(w);
    }
    auto tst_end = high_resolution_clock::now();
    auto tst_build_time = duration_cast<milliseconds>(tst_end - tst_start).count();
    
    // Note: This is also a rough approximation.
    double tst_memory_mb = (tst.getNodeCount() * sizeof(TSTNode)) / 1'048'576.0; // 1024*1024

    
    // --- 4. Print Build Report ---
    cout << fixed << setprecision(2); // Set output to 2 decimal places
    cout << "Trie built in " << trie_build_time << " ms, using " << trie_memory_mb << " MB. ";
    cout << "TST built in " << tst_build_time << " ms, using " << tst_memory_mb << " MB.\n";


    // --- 5. Main Query Loop ---
    string prefix;
    const int BENCHMARK_RUNS = 500;

    while (true) {
        cout << "\nEnter a prefix to search (or type 'exit' to quit): > ";
        cin >> prefix;

        if (prefix == "exit") break;
        prefix = lower(prefix);

        // --- Benchmark and Query Trie ---
        volatile size_t trie_sink = 0; // To prevent compiler optimization
        auto trie_q_start = high_resolution_clock::now();
        for (int i = 0; i < BENCHMARK_RUNS; ++i) {
            auto res = trie.getSuggestions(prefix);
            trie_sink += res.size();
        }
        auto trie_q_end = high_resolution_clock::now();
        auto trie_total_us = duration_cast<microseconds>(trie_q_end - trie_q_start).count();
        double trie_avg_us = trie_total_us / static_cast<double>(BENCHMARK_RUNS);
        
        auto trie_results = trie.getSuggestions(prefix); // Get results once to display

        cout << fixed << setprecision(1); // Set output to 1 decimal place for time
        cout << "\n--- Suggestion from Trie (found in " << trie_avg_us << " us) --\n";
        printSuggestions(trie_results);


        // --- Benchmark and Query TST ---
        // (Assuming TST method is findCompletions)
        volatile size_t tst_sink = 0; 
        auto tst_q_start = high_resolution_clock::now();
        for (int i = 0; i < BENCHMARK_RUNS; ++i) {
            auto res = tst.findCompletions(prefix);
            tst_sink += res.size();
        }
        auto tst_q_end = high_resolution_clock::now();
        auto tst_total_us = duration_cast<microseconds>(tst_q_end - tst_q_start).count();
        double tst_avg_us = tst_total_us / static_cast<double>(BENCHMARK_RUNS);

        auto tst_results = tst.findCompletions(prefix); // Get results once to display

        cout << "\n--- Suggestion from TST (found in " << tst_avg_us << " us) --\n";
        printSuggestions(tst_results);
    }

    return 0;
}
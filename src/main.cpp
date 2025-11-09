#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <iomanip> // For formatting output

// Include your headers (assuming they are in the 'include' path)
#include "Trie.h"
#include "TST.h"  

using namespace std;
using namespace std::chrono;

//Converts to lower char
static string lower(string s) {
    for (char &c : s)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

// Print the top 10
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
   //Load words from the words.txt
    string filepath = "./data/words.txt";
    ifstream fin(filepath);
    if (!fin.is_open()) {
        cerr << "Error: could not open file: " << filepath << "\n";
        return 1;
    }

    vector<string> words;
    string line;
    while (getline(fin, line)) {
        line = lower(line);
        if (!line.empty()) words.push_back(line);
    }

    fin.close();
    cout << "\n";
    cout << "    ___         __                                   __     __     \n";
    cout << "   /   | __  __/ /_____  _________  ____ ___  ____  / /__  / /____ \n";
    cout << "  / /| |/ / / / __/ __ \\/ ___/ __ \\/ __ `__ \\/ __ \\/ / _ \\/ __/ _ \\\n";
    cout << " / ___ / /_/ / /_/ /_/ / /__/ /_/ / / / / / / /_/ / /  __/ /_/  __/\n";
    cout << "/_/  |_\\__,_/\\__/\\____/\\___/\\____/_/ /_/ /_/ .___/_/\\___/\\__/\\___/ \n";
    cout << "                  / ____/___   ____  ____ /_/__                    \n";
    cout << "                 / __/ / __ \\/ __ `/ / __ \\/ _ \\                   \n";
    cout << "                / /___/ / / / /_/ / / / / /  __/                   \n";
    cout << "               /_____/_/ /_/\\__, /_/_/ /_/\\___/                    \n";
    cout << "                           /____/\n";
    cout << "\n";


    cout << "Building data structures ... \n";
    cout.flush(); //Make sure its outputs everything above before outputting build time and space

    //---Trie---
    Trie trie;
    auto trie_start = high_resolution_clock::now();
    for (const auto &w : words) {
        trie.insert(w);
    }
    auto trie_end = high_resolution_clock::now();
    auto trie_build_time = duration_cast<milliseconds>(trie_end - trie_start).count();

    double trie_memory_mb = (trie.getNodeCount() * sizeof(TrieNode)) / 1'048'576.0; // 1024*1024

    ///---TST---
    TST tst;
    auto tst_start = high_resolution_clock::now();
    for (const auto &w : words) {
        tst.insert(w);
    }
    auto tst_end = high_resolution_clock::now();
    auto tst_build_time = duration_cast<milliseconds>(tst_end - tst_start).count();

    double tst_memory_mb = (tst.getNodeCount() * sizeof(TSTNode)) / 1'048'576.0; // 1024*1024


    cout << fixed << setprecision(2); // 2 decimal places
    cout << "Trie built in " << trie_build_time << " ms, using " << trie_memory_mb << " MB. \n";
    cout << "TST built in " << tst_build_time << " ms, using " << tst_memory_mb << " MB.\n";

    //---loop---
    string prefix;
    const int BENCHMARK_RUNS = 500;

    while (true) {
        cout << "\nEnter a prefix to search (or type 'exit' to quit): > ";
        cin >> prefix;

        if (prefix == "exit") break;
        prefix = lower(prefix);

        //REALLY IMPORTANT!!!
        //Modern compilers tend to optimize and skip entire loops where values are not used
        //To prevent this, we can use a "sink" to make sure the code doesnt skip the for loop

        volatile size_t trie_sink = 0;
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
        cout << "\n--- Suggestion from Trie (found in " << (trie_avg_us) << " us) --\n";
        printSuggestions(trie_results);

        //Same idea as previous
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

        cout << "\n--- Suggestion from TST (found in " << (tst_avg_us) << " us) --\n";
        printSuggestions(tst_results);
    }

    return 0;
}
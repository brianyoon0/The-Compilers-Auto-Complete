#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "TST.h"
using namespace std;

static string lower(string s) {
    for (char &c : s)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

int main() {
    TST tst;

    ifstream fin("C:\\Users\\Brian\\CLionProjects\\The-Compilers-Auto-Complete\\data\\words.txt");
    if (!fin.is_open()) {
        cerr << "Error: could not open";
        return 1;
    }

    vector<string> words;
    string line;

    while (getline(fin, line)) {
        line = lower(line);
        if (!line.empty()) words.push_back(line);
    }
    fin.close();

    cout << "Loaded " << words.size() << " words.\n";

    auto start = chrono::high_resolution_clock::now();
    for (const auto &w : words) tst.insert(w);
    auto end = chrono::high_resolution_clock::now();

    auto build_time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "TST Performance Report\n";
    cout << "Total words loaded: " << words.size() << "\n";
    cout << "Build Time: " << build_time << "ms\n";
    cout << "Node count: " << tst.getNodeCount() << "\n";

    double memoryMB = tst.getNodeCount() * sizeof(TSTNode) / 1'000'000.0;

    cout << "Approx memory: " << memoryMB << "MB\n";
    cout << "=====================\n";
    string prefix;
    while (true) {
        cout << "Enter prefix (or exit)\n";
        cin >> prefix;

        if (prefix == "exit")break;
        prefix = lower(prefix);

        auto qstart = chrono::high_resolution_clock::now();
        auto results = tst.findCompletions(prefix);
        auto qend = chrono::high_resolution_clock::now();
        auto query_time = chrono::duration_cast<chrono::milliseconds>(qend - qstart).count();

        cout << "Query time: " << query_time << "µs\n";
        if (results.empty()){
            cout << "(no matches)\n";
            } else {
                for (auto &r : results) cout << " - " << r << "\n";
        }
    }
    return 0;
}
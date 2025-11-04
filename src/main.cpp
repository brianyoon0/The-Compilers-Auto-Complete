#include <iostream>
#include "TST.h"
using namespace std;

int main() {
    TST tst;

    tst.insert("computer");
    tst.insert("computation");
    tst.insert("compile");
    tst.insert("compiler");
    tst.insert("compact");
    tst.insert("company");

    string prefix;
    while (true) {
        cout << "Enter prefix (or exit)";
        cin >> prefix;
        if (prefix == "exit")break;

        auto results = tst.findCompletions(prefix);
        if (results.empty()) {
            cout << "No matches found. \n";
        } else {
            cout << "Completions: \n";
            for (const auto &r : results) {
                cout << " - " << r << endl;
            }
        }
        return 0;
    }
}
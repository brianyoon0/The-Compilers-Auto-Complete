#pragma once
#include <string>
#include <vector>
using namespace std;

//each node in the ternary search tree
struct TSTNode {
    char ch;
    bool isEnd;
    TSTNode *left, *equal, *right;

    TSTNode(char c) : ch(c), isEnd(false), left(nullptr), equal(nullptr), right(nullptr) {}
};

class TST {
public:
    TST();
    ~TST();

    void insert(const string &word);
    vector<string> findCompletions(const string &prefix) const;
    size_t getNodeCount() const{return nodeCount;}


private:
    TSTNode *root;
    size_t nodeCount = 0;

    TSTNode* insertRec(TSTNode *node, const string &word, int index);
    const TSTNode* searchPrefix(const TSTNode *node, const string &prefix, int index) const;
    void collect(const TSTNode *node, string &path, vector<string> &out, int limit) const;
    void freeAll(TSTNode *node);
};
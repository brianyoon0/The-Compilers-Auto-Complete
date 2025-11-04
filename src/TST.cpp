#include "TST.h"
#include <iostream>
using namespace std;

TST::TST() {
    root = nullptr;
}

TST::~TST() {
    freeAll(root);
}

void TST::freeAll(TSTNode *node) {
    if (!node) return;
    freeAll(node->left);
    freeAll(node->equal);
    freeAll(node->right);
    delete node;
}

void TST::insert(const string &word) {
    if (word.empty()) return;
    root = insertRec(root, word, 0);
}

TSTNode* TST::insertRec(TSTNode* node, const string &word, int index) {
    char c = word[index];
    if (!node) node = new TSTNode(c);

    if (c < node->ch)
        node->left = insertRec(node->left, word, index);
    else if (c > node->ch)
        node->right = insertRec(node->right, word, index);
    else {
        if (index + 1 == (int)word.length())
            node->isEnd = true;
        else
            node->equal = insertRec(node->equal, word, index + 1);
    }
    return node;
}

const TSTNode* TST::searchPrefix(const TSTNode* node, const string &prefix, int index) const {
    if (!node) return nullptr;

    char c = prefix[index];
    if (c < node->ch)
        return searchPrefix(node->left, prefix, index);
    else if (c > node->ch)
        return searchPrefix(node->right, prefix, index);
    else {
        if (index + 1 == (int)prefix.length())
            return node;
        return searchPrefix(node->equal, prefix, index + 1);
    }
}

void TST::collect(const TSTNode *node, string &path, vector<string> &out, int limit) const {
    if (!node || (int)out.size() >= limit) return;
    collect(node->left, path, out, limit);
    path.push_back(node->ch);
    if (node->isEnd) out.push_back(path);
    collect(node->equal, path, out, limit);
    path.pop_back();
    collect(node->right, path, out, limit);
}

vector<string> TST::findCompletions(const string &prefix) const {
    vector<string> results;
    if (prefix.empty() || !root) return results;

    const TSTNode *node = searchPrefix(root, prefix, 0);
    if (!node) return results;
    if (node->isEnd) results.push_back(prefix);
    string path = prefix;
    collect(node->equal, path, results, 10);
    return results;
}

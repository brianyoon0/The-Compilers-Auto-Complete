#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

struct TrieNode {
    unordered_map<char, unique_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const string& word);
    bool search(const string& word) const;
    vector<string> getSuggestions(const string& prefix) const;

    //Gets the total number of nodes in the trie
    size_t getNodeCount() const { return nodeCount; }

private:
    unique_ptr<TrieNode> root;
    size_t nodeCount; //useful to track memory usage

    TrieNode* findPrefixNode(const string& prefix) const;
    void findWordsFromNode(TrieNode* node, string currentPrefix, vector<string>& results) const;
};
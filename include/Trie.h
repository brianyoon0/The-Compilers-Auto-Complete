#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

struct TrieNode {
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& word);
    bool search(const std::string& word) const;
    std::vector<std::string> getSuggestions(const std::string& prefix) const;

private:
    std::unique_ptr<TrieNode> root;

    TrieNode* findPrefixNode(const std::string& prefix) const;
    void findWordsFromNode(TrieNode* node, std::string currentPrefix, std::vector<std::string>& results) const;
};
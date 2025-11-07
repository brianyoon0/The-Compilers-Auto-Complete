#include "Trie.H"

Trie::Trie() {
    root = std::make_unique<TrieNode>();
}

Trie::~Trie() {}

void Trie::insert(const std::string& word) {
    TrieNode* currentNode = root.get();

    for (char c : word) {
        if (currentNode->children.find(c) == currentNode->children.end()) {
            currentNode->children[c] = std::make_unique<TrieNode>();
        }
        currentNode = currentNode->children[c].get();
    }
    currentNode->isEndOfWord = true;
}

bool Trie::search(const std::string& word) const {
    TrieNode* node = findPrefixNode(word);
    return (node != nullptr && node->isEndOfWord);
}

std::vector<std::string> Trie::getSuggestions(const std::string& prefix) const {
    std::vector<std::string> results;
    TrieNode* prefixNode = findPrefixNode(prefix);

    if (prefixNode == nullptr) {
        return results;
    }

    if (prefixNode->isEndOfWord) {
        results.push_back(prefix);
    }
    
    findWordsFromNode(prefixNode, prefix, results);

    return results;
}

TrieNode* Trie::findPrefixNode(const std::string& prefix) const {
    TrieNode* currentNode = root.get();

    for (char c : prefix) {
        if (currentNode->children.find(c) == currentNode->children.end()) {
            return nullptr;
        }
        currentNode = currentNode->children[c].get();
    }
    return currentNode;
}

void Trie::findWordsFromNode(TrieNode* node, std::string currentPrefix, std::vector<std::string>& results) const {
    
    for (const auto& pair : node->children) {
        char childChar = pair.first;
        TrieNode* childNode = pair.second.get();

        std::string newPrefix = currentPrefix + childChar;

        if (childNode->isEndOfWord) {
            results.push_back(newPrefix);
        }

        findWordsFromNode(childNode, newPrefix, results);
    }
}
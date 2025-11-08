#include "Trie.H"

using namespace std;


Trie::Trie() : nodeCount(1) { // Sets nodes to 1 whenever initialized
    root = make_unique<TrieNode>(); //Use of unique ptr :0. Smart ptr that dynamically allocates space and 
    //self destructs when out of scope
}

Trie::~Trie() {}

void Trie::insert(const string& word) {
    TrieNode* currentNode = root.get();

    for (char c : word) {
        if (currentNode->children.find(c) == currentNode->children.end()) {
            currentNode->children[c] = make_unique<TrieNode>();
            nodeCount++; 
        }
        currentNode = currentNode->children[c].get();
    }
    currentNode->isEndOfWord = true;
}

bool Trie::search(const string& word) const {
    TrieNode* node = findPrefixNode(word);
    return (node != nullptr && node->isEndOfWord);
}

vector<string> Trie::getSuggestions(const string& prefix) const {
    vector<string> results;
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

TrieNode* Trie::findPrefixNode(const string& prefix) const {
    TrieNode* currentNode = root.get();

    for (char c : prefix) {
        if (currentNode->children.find(c) == currentNode->children.end()) {
            return nullptr;
        }
        currentNode = currentNode->children[c].get();
    }
    return currentNode;
}

void Trie::findWordsFromNode(TrieNode* node, string currentPrefix, vector<string>& results) const {
    
    for (const auto& pair : node->children) {
        char childChar = pair.first;
        TrieNode* childNode = pair.second.get();

        string newPrefix = currentPrefix + childChar;

        if (childNode->isEndOfWord) {
            results.push_back(newPrefix);
        }

        findWordsFromNode(childNode, newPrefix, results);
    }
}
#include "Trie.h"

void Trie::insert(const string& key, int s_id) {
    TrieNode* pCrawl = root;

    for (char c : key) {
        if (pCrawl->children.find(c) == pCrawl->children.end()) {
            pCrawl->children[c] = new TrieNode();
        }
        pCrawl = pCrawl->children[c];
    }

    pCrawl->s_ids.insert(s_id);
}

void Trie::search_recursive(TrieNode* node, const string& keyword, size_t pos, set<int>& result) {
    if (pos == keyword.size()) {
        result.insert(node->s_ids.begin(), node->s_ids.end());
        return;
    }

    char c = keyword[pos];
    if (node->children.find(c) != node->children.end()) {
        search_recursive(node->children[c], keyword, pos + 1, result);
    }
}

set<int> Trie::search(const string& keywords) {
    set<int> keyword_results;

    search_recursive(root, keywords, 0, keyword_results);

    return keyword_results;
}
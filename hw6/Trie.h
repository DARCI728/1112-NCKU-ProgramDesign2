#pragma once

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    set<int> s_ids;

    TrieNode() {}
};

class Trie {
   public:
    TrieNode* root;

    Trie() { root = new TrieNode(); }

    void insert(const string& key, int s_id);
    void search_recursive(TrieNode* node, const string& keyword, size_t pos, set<int>& result);
    set<int> search(const string& keywords);

   private:
};
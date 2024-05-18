#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Trie.h"

using namespace std;

class SearchEngine {
   public:
    void input(const string& corpus);
    void ouput(const string& query, const int& top_k);

   private:
    int totalDocuments = 0;
    Trie trie;
    vector<int> results;
    map<string, int> documentFrequencies;
    unordered_map<int, int> idf_sums;

    vector<string> split(const string& s, char delim);
    string to_lower(const string& s);
    string remove_nonalpha(const string& s);
    double idf(const int& totalDocuments, const int& documentFrequency);
    static bool mycmp(const pair<int, double>& a, const pair<int, double>& b);
};

#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    istringstream iss(s);
    string token;
    if (delim == ',')
    {
        getline(iss, token, delim);
        result.push_back(token);
        getline(iss, token);
        result.push_back(token);
    }
    else
    {
        while (getline(iss, token, delim))
        {
            result.push_back(token);
        }
    }
    return result;
}

inline string to_lower(const string &s)
{
    string tmp(s);
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
}

inline string remove_nonalpha(const string &s)
{
    string tmp(s);
    tmp.erase(remove_if(tmp.begin(), tmp.end(), [](unsigned char c)
                        { return !isalpha(c) && !isspace(c); }),
              tmp.end());
    return tmp;
}

struct TrieNode
{
    map<char, TrieNode *> children;
    set<int> s_ids;

    TrieNode() {}
};

class Trie
{
public:
    TrieNode *root;

    Trie() { root = new TrieNode(); }

    void insert(const string &key, int s_id);
    void search_recursive(TrieNode *node, const string &keyword, size_t pos, set<int> &result);
    set<int> search(const vector<string> &keywords);
};

void Trie::insert(const string &key, int s_id)
{
    TrieNode *pCrawl = root;

    for (char c : key)
    {
        if (pCrawl->children.find(c) == pCrawl->children.end())
        {
            pCrawl->children[c] = new TrieNode();
        }
        pCrawl = pCrawl->children[c];
    }

    pCrawl->s_ids.insert(s_id);
}

void Trie::search_recursive(TrieNode *node, const string &keyword, size_t pos, set<int> &result)
{
    if (pos == keyword.size())
    {
        result.insert(node->s_ids.begin(), node->s_ids.end());
        return;
    }

    char c = keyword[pos];
    if (node->children.find(c) != node->children.end())
    {
        search_recursive(node->children[c], keyword, pos + 1, result);
    }
}

set<int> Trie::search(const vector<string> &keywords)
{
    vector<set<int>> keyword_results(keywords.size());

    for (size_t i = 0; i < keywords.size(); ++i)
    {
        search_recursive(root, keywords[i], 0, keyword_results[i]);
    }

    set<int> result = keyword_results[0];
    for (size_t i = 1; i < keyword_results.size(); ++i)
    {
        set<int> new_result;
        set_intersection(result.begin(), result.end(), keyword_results[i].begin(), keyword_results[i].end(), inserter(new_result, new_result.begin()));
        result = new_result;
    }

    return result;
}

class SearchEngine
{
public:
    Trie trie;
    vector<string> keywords;
    set<int> results;
    void input(const string &corpus, const string &query);
};

void SearchEngine::input(const string &corpus, const string &query)
{
    ifstream corpus_file(corpus);
    ifstream query_file(query);

    if (!corpus_file)
    {
        cout << "Error opening file: " << corpus << '\n';
        exit(1);
    }

    if (!query_file)
    {
        cout << "Error opening file: " << query << '\n';
        exit(1);
    }

    string line;
    while (getline(corpus_file, line))
    {
        vector<string> parts = split(line, ',');
        int s_id = stoi(parts[0]);
        string article = remove_nonalpha((to_lower(parts[1])));
        vector<string> words = split(article, ' ');
        for (const string &word : words)
        {
            trie.insert(word, s_id);
        }
    }

    while (getline(query_file, line))
    {
        keywords = split(line, ' ');
        for (auto &entry : keywords)
        {
            entry = to_lower(entry);
        }

        results = trie.search(keywords);

        bool first = true;
        if (results.empty())
        {
            cout << "-1";
        }
        else
        {
            for (int entry : results)
            {
                if (first)
                {
                    cout << entry;
                    first = false;
                }
                else
                {
                    cout << " " << entry;
                }
            }
        }
        cout << '\n';
    }

    corpus_file.close();
    query_file.close();
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    if (argc != 3)
    {
        cout << "No input file." << '\n';
        return 0;
    }

    SearchEngine search_engine;
    search_engine.input(argv[1], argv[2]);
    return 0;
}
#include "SearchEngine.h"

void SearchEngine::input(const string& corpus) {
    ifstream corpus_file(corpus);

    if (!corpus_file) {
        cout << "Error opening file: " << corpus << '\n';
        exit(1);
    }

    string line;
    while (getline(corpus_file, line)) {
        vector<string> parts = split(line, ',');
        int s_id = stoi(parts[0]);
        string article = remove_nonalpha((to_lower(parts[1])));
        vector<string> words = split(article, ' ');
        unordered_map<string, bool> addFrequencies;
        unordered_set<string> uniqueWords;
        for (const string& word : words) {
            if (uniqueWords.find(word) == uniqueWords.end()) {
                trie.insert(word, s_id);
                ++documentFrequencies[word];
                uniqueWords.insert(word);
            }
        }
        ++totalDocuments;
    }
    corpus_file.close();
}

void SearchEngine::ouput(const string& query, const int& top_k) {
    ifstream query_file(query);

    if (!query_file) {
        cout << "Error opening file: " << query << '\n';
        exit(1);
    }

    string line;
    vector<string> keywords;
    set<int> results;

    while (getline(query_file, line)) {
        map<int, double> documentScores;
        keywords.clear();
        keywords = split(line, ' ');
        for (auto& keyword : keywords) {
            keyword = to_lower(keyword);
            results = trie.search(keyword);
            for (const auto& document : results) {
                documentScores[document] += idf(totalDocuments, documentFrequencies[keyword]);
            }
        }

        vector<pair<int, double>> documentScoreVec(documentScores.begin(), documentScores.end());
        if (documentScoreVec.size() > top_k) {
            partial_sort(documentScoreVec.begin(), documentScoreVec.begin() + top_k, documentScoreVec.end(), SearchEngine::mycmp);
        } else {
            sort(documentScoreVec.begin(), documentScoreVec.end(), SearchEngine::mycmp);
        }

        bool first = true;
        for (int i = 0; i < top_k; ++i) {
            int output;

            if (i < documentScoreVec.size() && documentScoreVec[i].second != 0) {
                output = documentScoreVec[i].first;
            } else {
                output = -1;
            }

            if (first) {
                cout << output;
                first = false;
            } else {
                cout << ' ' << output;
            }
        }

        cout << '\n';
    }

    query_file.close();
}

vector<string> SearchEngine::split(const string& s, char delim) {
    vector<string> result;
    istringstream iss(s);
    string token;
    if (delim == ',') {
        getline(iss, token, delim);
        result.push_back(token);
        getline(iss, token);
        result.push_back(token);
    } else {
        while (getline(iss, token, delim)) {
            result.push_back(token);
        }
    }
    return result;
}

string SearchEngine::to_lower(const string& s) {
    string tmp(s);
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    return tmp;
}

string SearchEngine::remove_nonalpha(const string& s) {
    string tmp(s);
    tmp.erase(remove_if(tmp.begin(), tmp.end(), [](unsigned char c) { return !isalpha(c) && !isspace(c); }), tmp.end());
    return tmp;
}

double SearchEngine::idf(const int& totalDocuments, const int& documentFrequency) {
    return log10((double)totalDocuments / (double)documentFrequency);
}

bool SearchEngine::mycmp(const pair<int, double>& a, const pair<int, double>& b) {
    if (a.second == b.second) {
        return a.first < b.first;
    } else {
        return a.second > b.second;
    }
}
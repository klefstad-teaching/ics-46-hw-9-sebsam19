#include "ladder.h"
#include <iostream>
#include <stack>
void error(string word1, string word2, string msg) {
    cout << msg << word1 << word2;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    std::set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (string words : word_list) {
            if (is_adjacent(last_word, words)) {
                if (visited.find(words) != visited.end()) {
                    visited.insert(words);
                    vector<string> new_ladder(ladder);
                    new_ladder.push_back(words);
                    if (words == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};

}

bool is_adjacent(const string& word1, const string& word2) {
    int diff = 0;
    if (edit_distance_within(word1, word2, 1) == 1) {
        if (abs(static_cast<int>((word1.size() - word2.size()))) == 1) {
            string longest = (word1.size() > word2.size()) ? word1 : word2;
            string shortest = (word1.size() < word2.size()) ? word1 : word2;
            for (size_t i = 0; i < longest.size(); ++i) {
                string substring = longest.substr(0, i) + longest.substr(i+1);
                if (substring == shortest) {
                    return true;
                }
            }
        }

        if (word1.size() == word2.size()) {
            for (size_t i = 0; i < word1.size(); ++i) {
                if (word1[i] != word2[i]) {
                    diff++;
                }
            }
            return diff == 1;
        }  
    } 
    return false;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    vector<vector<int>> choices(str1.size() + 1, vector<int>(str2.size() + 1, 0));
    int cost = 0;
    //making the matrix
    for (size_t i = 0; i <= str1.size(); ++i) {
        choices[i][0] = i;
    }

    for (size_t j = 0; j <= str2.size(); ++j) {
        choices[0][j] = j;
    }

    //populating matrix
    for (size_t i = 1; i <= str1.size(); ++i) {
        for (size_t j = 1; j<= str2.size(); ++j) {
            if (str1[i] == str2[j]) {
                cost = 0;
            } else {
                cost = 1;
            }

            choices[i][j] = min(choices[i-1][j] + 1, min(choices[i][j-1] + 1, choices[i-j][j-1] + cost));
        }
    }
    return choices[str1.size()][str2.size()] <= d;
}

// void load_words(set<string> & word_list, const string& file_name);
// void print_word_ladder(const vector<string>& ladder);
// void verify_word_ladder();
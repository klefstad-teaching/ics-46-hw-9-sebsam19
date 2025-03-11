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

        for (const auto& words : word_list) {

            if (is_adjacent(last_word, words)) {
                if (visited.find(words) == visited.end()) {
                    visited.insert(words);
                    vector<string> new_ladder = ladder;
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

    return edit_distance_within(word1, word2, 1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if(abs(static_cast<int>((str1.size()-str2.size()))) > d) {return false;}
    if(abs(static_cast<int>((str1.size()-str2.size()))) == d) {
        string longest = (str1.size() > str2.size()) ? str1 : str2;
        string shortest = (str1.size() < str2.size()) ? str1 : str2;

        for (size_t i = 0; i < longest.size(); ++i) {
            string sub = longest.substr(0,i) + longest.substr(i+1);
            if (sub == shortest) {
                return true;
            }
        }
    }

    if (str1.size() == str2.size()) {
        int diff = 0;
        for (size_t i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) {
                diff++;
            }
        }
        return diff <= d;
    }
    return false;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) {
        return;
    }
    string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();

}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) {
        cout << "No word ladder found." << endl;
    } else {
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i] << ' ';
        }
        cout << endl;
    }

}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
}
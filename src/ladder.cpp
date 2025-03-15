#include "ladder.h"

void error(string word1, string word2, string msg){
cerr << msg << " | " << word1 << " -> " << word2;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int this_size = str1.size(), other_size = str2.size();
    if (str1 == str2) return 0;
    if (abs(this_size - other_size) > 1) return 0;
    int this_index = 0, other_index = 0, difference = 0;
    for (; this_index < this_size && other_index < other_size;){
        if (str1[this_index] != str2[other_index]){
            difference++;
            if (difference > d) return 0;
            if (this_size > other_size) this_index++;
            else if (this_size < other_size) other_index++;
            else {this_index++; other_index++;}
        } else {this_index++; other_index++;}
    }
    if (this_index < this_size || other_index < other_size) difference++;
    return difference == d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) return {};
    set<string> local_set = word_list;
    queue<vector<string>> queue_path;
    queue_path.push({begin_word});
    local_set.erase(begin_word);
    while (!queue_path.empty()){
        vector<string> word_ladder = queue_path.front();
        queue_path.pop();
        string cur_word = word_ladder.back();
        if (cur_word == end_word) return word_ladder;
        for (auto word = local_set.begin(); word != local_set.end();) {
            if (is_adjacent(cur_word, *word)){
                vector<string> updated_ladder = word_ladder;
                updated_ladder.push_back(*word);
                queue_path.push(updated_ladder);
                word = local_set.erase(word);
            } else {++word;}
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream curFile(file_name);
    if (!curFile.is_open()){cerr << "Cannot open file!" << endl;}
    for (string word; getline(curFile, word);) {if (!word.empty()) word_list.insert(word);}
    curFile.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (auto word : ladder){cout << word << " ";}
        cout << endl;
    }
    else {cout << "No word ladder found." << endl;}
}

void verify_word_ladder(){
    set<string> unordered_ladder;
    load_words(unordered_ladder, "src/words.txt");
    if (generate_word_ladder("cat", "dog", unordered_ladder).size() == 4){cout << "TEST CASE 1 : PASSED" << endl;}
    if (generate_word_ladder("marty", "curls", unordered_ladder).size() == 6) {cout << "TEST CASE 2 : PASSED" << endl;}
    if (generate_word_ladder("code", "data", unordered_ladder).size() == 6) {cout << "TEST CASE 3 : PASSED" << endl;}
    if (generate_word_ladder("work", "play", unordered_ladder).size() == 6) {cout << "TEST CASE 4 : PASSED" << endl;}
    if (generate_word_ladder("sleep", "awake", unordered_ladder).size() == 8) {cout << "TEST CASE 5 : PASSED" << endl;}
    if (generate_word_ladder("car", "cheat", unordered_ladder).size() == 4) {cout << "TEST CASE 6 : PASSED" << endl;} 
}

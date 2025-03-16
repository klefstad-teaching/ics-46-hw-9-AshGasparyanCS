#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <unordered_set>
#include "ladder.h"

using namespace std;

bool is_adjacent(const string& word1, const string& word2)
{
    if (word1.length() != word2.length())
    {
        return false;
    }
    int diff_count = 0;
    for (size_t i = 0; i < word1.length(); i++)
    {
        if (word1[i] != word2[i])
        {
            diff_count++;
            if (diff_count > 1)
            {
                return false;
            }
        }
    }
    return diff_count == 1;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop
        string last_word = ladder.back();
        for(const string& word : word_list)
        {
            if(is_adjacent(last_word, word))
            {
                if(visited.find(word) == visited.end())
                {
                    visited.insert(word);

                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word)
                    {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}
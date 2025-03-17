#include "ladder.h"

using namespace std;

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word)
    {
        return {begin_word};
    }
    if(word_list.find(end_word) == word_list.end())
    {
        error(begin_word, end_word, "End word not in word list.")
        return{};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = current_ladder.back();

        for(const string& candidate : word_list)
        {
            if(is_adjacent(last_word, candidate) && !visited.count(candidate))
            {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(candidate);
                if (candidate == end_word)
                {
                    return new_ladder;
                }

                visited.insert(candidate);
                ladder_queue.push(new_ladder);
            }
        }
    }

    error(begin_word, end_word, "No ladder found.");
    return {};
}
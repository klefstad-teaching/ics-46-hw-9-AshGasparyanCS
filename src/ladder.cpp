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
        error(begin_word, end_word, "End word not in word list.");
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

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    const size_t m = str1.length();
    const size_t n = str2.length();

    if(abs(int(m - n)) > d)
    {
        return false;
    }

    vector<vector<int> dp(m + 1, vector<int>(n + 1, 0 ));

    for(size_t i = 0; i <= m; ++i)
    {
        dp[i][0] = i;
    }

    for(size_t j = 0; j <= n; ++j)
    {
        dp[0][j] = j;
    }

    for(size_t i = 1; i <= m; ++i)
    {
        for(size_t j = 1; j <= n; ++j)
        {
            int cost = (str1[i-1] == str2[j-1]) ? 0 : 1;
            dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + cost});
        }
    }
    return dp[m][n] <= d;
}

void load_words(set<string>& word_list, const string& file_name)
{
    ifstream in(file_name);
    if(!in)
    {
        error(file_name, "", "could not be opened");
        return;
    }
    string word;
    while(in >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        return;
    }

    cout << "Word ladder found: ";
    for(size_t i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i];
        if(i < ladder.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
}

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")\n";
}
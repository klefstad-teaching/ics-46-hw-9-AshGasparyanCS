#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg)
{
    cerr << word1 << word2 << msg;
}

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    int length1 = str1.size();
    int length2 = str2.size();
    if(abs(length1 - length2) > d)
    {
        return false;
    }

    vector<vector<int>>dp(length1 + 1, vector<int>(length2 + 1, 0));

    for(int i = 0; i <= length1; ++i)
    {
        dp[i][0] = i;
    }
    for(int j = 0; j <= length2; ++j)
    {
        dp[0][j] = j;
    }

    for(int i = 1; i <= length1; ++i)
    {
        for(int j = 1; j <= length2; ++j)
        {
            if(str1[i-1] == str2[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
            }
            else
            {
                dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]}) + 1;
            }
        }
    }
    return dp[length1][length2] <= d;
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    vector<string> start_ladder = {begin_word};
    ladder_queue.push(start_ladder);
    set<string> visited;
    visited.insert(begin_word);
    vector<string> empty;

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for(const string& word : word_list)
        {
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == end_word)
                {
                    return new_ladder;
                }

                ladder_queue.push(new_ladder);
                visited.insert(word);
            }
        }
    }
    return empty;
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if(!in)
    {
        error(file_name, "could not be opened." , "");
        return;
    }
    
    string word;
    while(in >> word)
    {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found.\n";
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i)
    {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
}
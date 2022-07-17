#include <bits/stdc++.h>
using namespace std;
set<char> ss;
bool dfs(char i, char org, char last, map<char, vector<vector<char>>> &mp)
{
    bool rtake = false;
    for (auto r : mp[i])
    {
        bool take = true;
        for (auto s : r)
        {
            if (s == i)
                break;
            if (!take)
                break;
            if (!(s >= 'A' && s <= 'Z') && s != 'e')
            {
                ss.insert(s);
                break;
            }
            else if (s == 'e')
            {
                if (org == i || i == last)
                    ss.insert(s);
                rtake = true;
                break;
            }
            else
            {
                take = dfs(s, org, r[r.size() - 1], mp);
                rtake |= take;
            }
        }
    }
    return rtake;
}
int main()
{
    cout << "NAME - Vivek Srivastav" << endl;
    cout << "ROLL NO - 2K19/CO/437" << endl
         << endl;
    int i, j;
    ifstream fin("First.txt"); //make a .txt in which we have to enter production in that manner : S->ABC|de|Fg
    string num;
    vector<int> fs;
    vector<vector<int>> a;
    map<char, vector<vector<char>>> mp;
    char start;
    bool flag = 0;
    cout << "Grammar: " << '\n'; 
    while (getline(fin, num))
    {
        if (flag == 0)
            start = num[0], flag = 1;
        cout << num << '\n';
        vector<char> temp;
        char s = num[0];
        for (i = 3; i < num.size(); i++)
        {
            if (num[i] == '|')
            {
                mp[s].push_back(temp);
                temp.clear();
            }
            else
                temp.push_back(num[i]);
        }
        mp[s].push_back(temp);
    }
    map<char, set<char>> fmp;
    for (auto q : mp)
    {
        ss.clear();
        dfs(q.first, q.first, q.first, mp);
        for (auto g : ss)
            fmp[q.first].insert(g);
    }
    cout << '\n';
    cout << "FIRST: " << '\n';
    for (auto q : fmp)
    {
        string ans = "";
        ans += q.first;
        ans += " = {";
        for (char r : q.second)
        {
            ans += r;
            ans += ',';
        }
        ans.pop_back();
        ans += "}";
        cout << ans << '\n';
    }
    return 0;
}
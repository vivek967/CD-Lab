#include <bits/stdc++.h>
using namespace std;

vector<string> G[1000];
set<char> FIRST[1000];
bool vis[1000];

void F(int start)
{

    if (vis[start])
        return;

    for (int i = 0; i < G[start].size(); i++)
    {
        if (G[start][i] == "~")
        {
            FIRST[start].insert('~');
        }
        else if (!isupper(G[start][i][0]))
        {
            FIRST[start].insert(G[start][i][0]);
        }
        else
        {
            bool flag;
            int k;
            for (k = 0; k < G[start][i].length(); k++)
            {
                char nxt = G[start][i][k];
                if (!isupper(nxt))
                {
                    FIRST[start].insert(nxt);
                    break;
                }

                if (!vis[nxt - 'A'])
                    F(nxt - 'A');

                flag = 0;
                for (set<char>::iterator itr = FIRST[nxt - 'A'].begin(); itr != FIRST[nxt - 'A'].end(); itr++)
                {
                    if ((*itr) == '~')
                    {
                        flag = 1;
                    }
                    else
                        FIRST[start].insert(*itr);
                }
                if (!flag)
                    break;
            }
            if (k == G[start][i].length())
            {
                FIRST[start].insert('~');
            }
        }
    }
    vis[start] = 1;
}

int main()
{
    int test = 0, t = 0, i, j, k, n, m;
    string str;

    fstream fin, fout;
    fin.open("input.txt");
    fout.open("output.txt");
    cout << "\nEnter the number of grammars: ";
    fin >> test;
    cout << test << "\n";

    while (t++ != test)
    {
        for (i = 0; i < 1000; i++)
        {
            G[i].clear();
            FIRST[i].clear();
        }
        memset(vis, 0, sizeof(vis));
        cout << "\n\nEnter number of nonterminals: ";
        fin >> n;
        cout << n << "\n";
        for (i = 0; i < n; i++)
        {
            cout << "\nEnter the productions for NT " << (char)(i + 'A') << ": ";
            fin >> m;
            cout << m << " ";
            for (j = 0; j < m; j++)
            {
                fin >> str;
                cout << str << " ";
                G[i].push_back(str);
            }
        }
        for (i = 0; i < n; i++)
        {
            F(i);
        }
        fout << "\n"
             << t << ")\nFIRST TABLE: \n";
        cout << "\n"
             << t << ")\nFIRST TABLE: \n";
        for (i = 0; i < n; i++)
        {
            fout << '\t' << char(i + 'A') << "-> ";
            cout << '\t' << char(i + 'A') << "-> ";
            for (set<char>::iterator itr = FIRST[i].begin(); itr != FIRST[i].end(); itr++)
            {
                fout << (*itr) << " ";
                cout << (*itr) << " ";
            }
            fout << "\n";
            cout << "\n";
        }
    }
}
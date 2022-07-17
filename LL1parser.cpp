#include <bits/stdc++.h>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <deque>
#include <sstream>
#include <regex>
#include <iomanip>

using namespace std;
multimap<string, deque<string>> m;
map<string, bool> NT;
set<string> Term;
map<string, int> PosTerm, PosNT;
map<string, vector<string>> First;
map<string, set<string>> Follow;
vector<string> string_test;
void ReadGrammar()
{
	string s, flecha;
	string k = "@", ini;
	while (getline(cin, s))
	{
		if (s == "string_test:")
			break;
		stringstream in(s);
		in >> ini >> flecha;
		if (k == "@")
			NT[ini] = 1;
		else
			NT[ini] = 0;
		deque<string> valores;
		while (in >> k)
		{
			if (k == "|")
				m.insert({ini, valores}), valores.clear();
			else
			{
				bool ok = 1;
				for (auto ch : k)
					if (ch >= 'A' && ch <= 'Z')
						ok = 0;
				valores.push_back(k);
				if (ok)
					Term.insert(k);
			}
		}
		m.insert({ini, valores});
	}
	getline(cin, s);
	stringstream in(s);
	string_test = {};
	while (in >> k)
		string_test.push_back(k);
	string_test.push_back("$");
	reverse(string_test.begin(), string_test.end());
}
map<string, int> vis;
vector<string> DfsFirst(string e)
{
	vis[e] = 1;
	if (!m.count(e))
	{
		First[e] = {e};
		return {e};
	}
	vector<string> res;
	for (auto val : m)
	{
		if (val.first == e)
		{
			vector<string> ter;
			ter = DfsFirst(val.second.front());
			for (auto u : ter)
				res.push_back(u);
		}
	}
	First[e] = res;
	return res;
}
void FindFirst()
{
	for (auto e : Term)
		First[e] = {e};
	for (auto e : NT)
	{
		if (!vis[e.first])
			First[e.first] = DfsFirst(e.first);
	}
}
map<string, int> visg;
void DfsFollow(string e)
{
	map<string, int> used;
	vector<string> st;
	st.push_back(e);
	while (st.size())
	{
		e = st.back();
		if (visg[e])
		{
			st.pop_back();
			if (st.size())
			{
				string v = st.back();
				for (auto ele : Follow[e])
					Follow[v].insert(ele);
			}
			used[e] = 0;
			continue;
		}
		visg[e] = used[e] = 1;
		for (auto val : m)
		{
			deque<string> d = val.second;
			for (int i = 0; i < d.size(); i++)
			{
				if (e == d[i])
				{
					bool ok = 0;
					if (i + 1 < d.size())
					{
						vector<string> res = First[d[i + 1]];
						for (auto v : res)
						{
							if (v == "Ɛ")
								ok = 1;
							else
								Follow[e].insert(v);
						}
					}
					if (i + 1 >= d.size() || ok)
					{
						if (used[val.first])
						{
							for (int j = 0; j < st.size(); j++)
							{
								if (st[j] == val.first)
								{
									st.insert(st.begin() + j, e);
									break;
								}
							}
						}
						else
							st.push_back(val.first);
					}
				}
			}
		}
	}
}
void FindFollow()
{
	for (auto e : NT)
	{
		if (e.second)
			Follow[e.first].insert("$");
		if (!visg[e.first])
			DfsFollow(e.first);
	}
}
deque<string> table[22][22];
void TableLL()
{
	for (auto e : First)
	{
		for (auto v : e.second)
		{
			deque<string> d;
			if (v == "Ɛ")
			{
				d = {"Ɛ"};
				for (auto val : Follow[e.first])
				{
					table[PosNT[e.first]][PosTerm[val]] = d;
				}
			}
			else
			{
				for (auto val : m)
				{
					if (val.first == e.first)
					{
						bool ok = 0;
						for (auto u : First[val.second.front()])
						{
							if (v == u)
								ok = 1;
						}
						if (ok)
						{
							d = val.second;
							table[PosNT[e.first]][PosTerm[v]] = d;
							break;
						}
					}
				}
			}
		}
	}
}

void ShowFirst()
{
	cout << "First: \n";
	for (auto e : First)
	{
		cout << e.first << " -> ";
		for (auto v : First[e.first])
			cout << v << " ";
		cout << endl;
	}
	cout << endl;
}
void ShowFollow()
{
	cout << "Follow: \n";
	for (auto e : Follow)
	{
		cout << e.first << " -> ";
		for (auto v : Follow[e.first])
			cout << v << " ";
		cout << endl;
	}
	cout << endl;
}
void ShowTable()
{
	cout << "Parsing Table:\n";
	int w = 9;
	cout << string(2, ' ');
	for (auto v : Term)
	{
		int l = (w - v.size()) / 2;
		int r = w - l - v.size();
		cout << "|" << string(l, ' ') << v << string(r, ' ');
	}
	cout << endl;
	for (auto v : Term)
		cout << string(w + 1, '-');
	cout << endl;
	for (auto u : First)
	{
		if (!m.count(u.first))
			continue;
		cout << setw(2) << left << u.first;
		for (auto v : Term)
		{
			string line;
			for (auto e : table[PosNT[u.first]][PosTerm[v]])
				line += e + " ";
			int l = (w - (int)line.size()) / 2;
			int r = w - l - line.size();
			if (line == "Ɛ ")
				r++;
			cout << "|" << string(l, ' ') << line << string(r, ' ');
		}
		cout << endl;
	}
	for (auto v : Term)
		cout << string(w + 1, '-');
	cout << "\n\n";
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ReadGrammar();
	
	FindFirst();
	FindFollow();
	Term.insert("$");
	int cntTerm = 0;
	for (auto e : Term)
		PosTerm[e] = cntTerm++;
	int cntNT = 0;
	for (auto e : NT)
		PosNT[e.first] = cntNT++;
	
	ShowFirst();

	ShowFollow();
	for (int i = 0; i < cntNT; i++)
		for (int j = 0; j < cntTerm; j++)
		{
			table[i][j] = {"__"};
		}
	TableLL();
	ShowTable();
	
}
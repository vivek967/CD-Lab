// Vivek Srivastav Roll no: 2K19/CO/437
// Write a program to convert left recursive grammar to right recursive grammar.

#include <bits/stdc++.h>
using namespace std;
int max_char;

char next_char() {
    max_char++;
    return max_char;
}

void print_map(unordered_map<char,vector<string>>& m) {
    for(auto &i : m){
            cout << i.first << "->";
            for(int j = 0 ; j < i.second.size() ; j++) {
                cout << i.second[j];
                if(j != i.second.size() -1)
                    cout << "|";
            }
            cout << "\n";
        }
}

void parse_string(string &s,unordered_map<char,vector<string>>& m) {
    int i = 0;
   
    // skip all charcters before ->
    while(s[i] != '>') i++;
    i++;

    string str;
    for(;i < s.size();i++) {
        if(s[i] == '|') {
            m[s[0]].push_back(str);
            str = "";
        }
        else 
            str.push_back(s[i]);
    }
    m[s[0]].push_back(str);
} 

void remove_leftrec(char c,vector<string>& arr,unordered_map<char,vector<string>>& ans) {
    
    int idx = 0;
    for(; idx < arr.size() ; idx++)
        if(arr[idx][0] == c) 
            break;

    if(idx == arr.size()) {
        ans[c] = arr;
        return;
    }

    vector<string> nv,nv2;
    char next = next_char();

    for(int i = 0 ; i < arr.size() ; i++) {
        if(idx == i) continue;
        nv.push_back(arr[i]+next);
    }

    ans[c] = nv;
    ans[next].push_back(arr[idx].substr(1) + next);
    ans[next].push_back("epsilon");
}

int main()
{
    int n;
    cout << "ENTER NUMBER OF PRODUCTIONS : ";
    cin >> n;
    cout << "\nWrite production in this  manner : E->Ea|ba (no spaces) and production also  deterministic\n\n";

    /*
    example 1:
        A->AB|c|d
        B->a|b

     answer
        A->cT|dT
        T->BT|epsilon            
        B->a|b

  
    */ 

    unordered_map<char, vector<string>> m;
    while (n--) {
        string s;
        cin >> s;

        for(int i : s) {
            if(i >= 'A' and i <= 'Z')
                max_char = max(max_char,i);
        }
        
        parse_string(s,m);
    }

    // print_map(m);
    unordered_map<char,vector<string>> ans;



    // assuming grammar is deterministic
    for(auto& i : m) {
        remove_leftrec(i.first,i.second,ans);        
    }
    cout << "__________________________________________________";
    cout << "\nProductions after removing left recursion and it's convert into right recursion is that: - \n";
    print_map(ans);


    return 0;
}
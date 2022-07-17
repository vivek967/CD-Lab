#include<bits/stdc++.h>
using namespace std;
int main()
{
    cout<<"Enter the production:"; // In this way S->Sa/b
    string line;
    cin>>line;
    char nt=line[0],alpha=line[4],beta=line[6];
    cout<<nt<<"->"<<beta<<nt<<"'\n"<<nt<<"'->"<<alpha<<nt<<"'";
}
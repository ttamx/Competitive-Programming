#include<bits/stdc++.h>

using namespace std;

string pi="314159265358979323846264338327";

void runcase(){
    string s;
    cin >> s;
    int i=0;
    while(i<s.size()&&s[i]==pi[i])i++;
    cout << i << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
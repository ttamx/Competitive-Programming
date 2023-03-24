#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<multiset<char>> v(m);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            v[j].emplace(s[j]);
        }
    }
    for(int i=1;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            v[j].erase(v[j].find(s[j]));
        }
    }
    for(int i=0;i<m;i++)cout << *v[i].begin();
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
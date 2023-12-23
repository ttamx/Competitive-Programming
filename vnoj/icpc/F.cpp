#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string a,b;
    cin >> a >> b;
    vector<char> v[4];
    for(int i=0;i<a.size();i+=2)v[0].emplace_back(a[i]);
    for(int i=1;i<a.size();i+=2)v[1].emplace_back(a[i]);
    for(int i=0;i<b.size();i+=2)v[2].emplace_back(b[i]);
    for(int i=1;i<b.size();i+=2)v[3].emplace_back(b[i]);
    for(int i=0;i<4;i++)sort(v[i].begin(),v[i].end());
    cout << (v[0]==v[2]&&v[1]==v[3]?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
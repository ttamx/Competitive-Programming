#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    int n,k;
    cin >> n >> k >> s;
    vector<int> cnt(26);
    for(auto x:s)cnt[x-'a']++;
    int res=0;
    for(auto x:cnt)res+=x&1;
    cout << (res-1<=k?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
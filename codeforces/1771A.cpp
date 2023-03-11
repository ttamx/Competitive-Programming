#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(1e5+1);
    int mn=1e5,mx=1;
    for(auto &x:a)cin >> x,mn=min(mn,x),mx=max(mx,x),cnt[x]++;
    if(mn==mx)cout << 1ll*cnt[mn]*(cnt[mn]-1) << '\n';
    else cout << 1ll*cnt[mn]*cnt[mx]*2 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
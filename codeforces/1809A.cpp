#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int cnt[10]={};
    for(auto x:s)cnt[x-'0']++;
    int mx=0;
    for(int i=0;i<10;i++){
        mx=max(mx,cnt[i]);
    }
    int n=s.size();
    if(mx==n)cout << -1 << '\n';
    else cout << max(n,2*mx) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    vector<int> a(n);
    for(auto&x:a)cin >> x;
    for(auto &x:s)x-='A';
    int ans=0;
    for(int j=0;j<26;j++){
        vector<int> cnt(26);
        for(auto x:s)cnt[x]++;
        for(auto x:cnt)ans=max(ans,x);
        for(int i=0;i<n;i++){
            s[i]+=a[i];
            s[i]%=26;
        }
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
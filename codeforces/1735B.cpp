#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int mn=2e9;
    vector<int> a(n);
    for(auto &x:a)cin >> x,mn=min(mn,x);
    mn=2*mn-1;
    long long ans=0;
    for(auto x:a)ans+=max(0,(x+mn-1)/mn-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
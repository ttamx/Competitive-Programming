#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m),c;
    for(auto &x:a)cin >> x,c.emplace_back(x);
    for(auto &x:b)cin >> x,c.emplace_back(x);
    c.emplace_back(0);
    c.emplace_back(1e8);
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    int l=0,r=0;
    int ans1=n+m,ans2=0;
    for(auto x:c){
        while(l<n&&a[l]<=x)l++;
        while(r<m&&b[r]<x)r++;
        if(n-l+r<ans1){
            ans1=n-l+r;
            ans2=x;
        }
    }
    cout << ans2 << ' ' << ans1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
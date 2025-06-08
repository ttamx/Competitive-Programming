#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    sort(a.begin(),a.end(),[&](pair<int,int> l,pair<int,int> r){
        int vl=l.first-l.second;
        int vr=r.first-r.second;
        return vl>vr||(vl==vr&&l.first>r.first);
    });
    ll cur=0,ans=0;
    for(auto [x,y]:a){
        cur=max(cur,(ll)x)-y;
        ans+=y;
    }
    cout << ans+cur << "\n";
}
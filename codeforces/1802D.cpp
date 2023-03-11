#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    multiset<int> ms;
    for(auto &[x,y]:a){
        cin >> x >> y;
        ms.emplace(y);
    }
    sort(a.rbegin(),a.rend());
    int mx=-2e9,ans=2e9;
    for(auto [x,y]:a){
        ms.erase(ms.find(y));
        auto it=ms.lower_bound(x);
        ans=min(ans,abs(x-mx));
        if(it!=ms.end())ans=min(ans,abs(x-max(mx,*it)));
        if(it!=ms.begin())ans=min(ans,abs(x-max(mx,*prev(it))));
        mx=max(mx,y);
    }
    cout << ans << '\n';
}
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
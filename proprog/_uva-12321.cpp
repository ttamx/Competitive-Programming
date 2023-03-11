#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,n;
    while(cin >> m >> n){
        if(m==0&&n==0)break;
        vector<pair<int,int>> a(n);
        for(auto &[x,y]:a){
            int p,r;
            cin >> p >> r;
            x=max(0,p-r);
            y=min(m,p+r);
        }
        sort(a.begin(),a.end());
        multiset<pair<int,int>> ms;
        ms.emplace(0,0);
        for(auto [x,y]:a){
            auto it=ms.lower_bound({x,0});
            if(it==ms.end())continue;
            int val=it->second+1;
            it=ms.lower_bound({y,0});
            if(it!=ms.end()&&val>=it->second)continue;
            it=ms.emplace(y,val);
            while(it!=ms.begin()&&prev(it)->second>=val)ms.erase(prev(it));
        }
        if(prev(ms.end())->first<m)cout << -1 << '\n';
        else cout << n-prev(ms.end())->second << '\n';
    }
}
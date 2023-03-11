#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<int,vector<pair<int,int>>> adj;
    for(int i=0;i<n;i++){
        int k;
        cin >> k;
        vector<int> v;
        int mx=0;
        for(int j=0;j<k;j++){
            int x;
            cin >> x;
            if(x>mx){
                mx=x;
                v.emplace_back(mx);
            }
        }
        for(int j=0;j<v.size();j++){
            adj[mx].emplace_back(v[j],v.size()-j);
        }
    }
    multiset<pair<int,int>> ms;
    ms.emplace(0,0);
    int ans=0;
    for(auto [x,v]:adj){
        int val=0;
        for(auto [f,w]:v){
            val=max(val,prev(ms.lower_bound({f,0}))->second+w);
        }
        ans=max(ans,val);
        if(val>prev(ms.end())->second)ms.emplace(x,val);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
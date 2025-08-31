#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<tuple<int,int,int>> e;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            e.emplace_back(a[i][j],i,j);
        }
    }
    sort(e.rbegin(),e.rend());
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u)->int {
        return fa[u]=fa[u]==u?u:fp(fa[u]);
    };
    auto merge=[&](int u,int v)->bool {
        u=fp(u),v=fp(v);
        if(u>v)swap(u,v);
        if(u==v)return false;
        return fa[v]=u,true;
    };
    vector<pair<int,int>> ans;
    ll base=0;
    for(auto [w,u,v]:e){
        u=fp(u),v=fp(v);
        if(merge(u,v)){
            base+=w;
            ans.emplace_back(u,v);
        }
    }
    cout << base << "\n";
    for(auto [u,v]:ans){
        cout << u+1 << " " << v+1 << "\n";
    }
}
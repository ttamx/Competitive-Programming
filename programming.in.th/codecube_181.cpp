#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,p;
    cin >> n >> m >> p;
    vector<tuple<int,int,int>> e(m);
    for(auto &[x,y,z]:e)cin >> x >> y >> z;
    vector<pair<int,int>> c(p);
    for(auto &[x,y]:c)cin >> x >> y;
    int l=1,r=1e9+1;
    while(l<r){
        int mid=(l+r+1)/2;
        vector<int> pa(n+1);
        iota(pa.begin(),pa.end(),0);
        function<int(int)> fp=[&](int u){
            if(pa[u]==u)return u;
            return pa[u]=fp(pa[u]);
        };
        for(auto [x,y,z]:e)if(z<mid&&fp(x)!=fp(y))pa[pa[x]]=pa[y];
        bool ok=true;
        for(auto [x,y]:c)if(fp(x)==fp(y))ok=false;
        if(ok)l=mid;
        else r=mid-1;
    }
    cout << (l<=1e9?l:-1);
}
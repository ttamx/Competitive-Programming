#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    int k,n;
    cin >> k >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    auto dist=[&](int i,int j){
        ll dx=a[i].first-a[j].first;
        ll dy=a[i].second-a[j].second;
        return dx*dx+dy*dy;
    };
    auto calc=[&](ll d){
        vector<int> p(n);
        iota(p.begin(),p.end(),0);
        function<int(int)> fp=[&](int u){
            return p[u]=p[u]==u?u:fp(p[u]);
        };
        for(int i=0;i<n;i++)for(int j=0;j<i;j++)if(dist(i,j)<=d)p[fp(i)]=fp(j);
        int res=0;
        for(int i=0;i<n;i++)if(i==fp(i))res++;
        return res;
    };
    ll l=0,r=1e18;
    while(l<r){
        ll m=(l+r)/2;
        if(calc(m)<=k)r=m;
        else l=m+1;
    }
    cout << fixed << setprecision(2) << sqrt(l) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
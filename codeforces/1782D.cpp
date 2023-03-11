#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    map<ll,vector<pair<int,int>>> mp;
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++){
        for(int j=1;j<n;j++){
            ll dif=a[j]-a[i];
            int k=sqrt(dif);
            for(int l=1;l<=k;l++){
                if(dif%l)continue;
                int r=dif/l;
                if((r+l)&1)continue;
                ll v=(r-l)/2;
                ll x=v*v-a[i];
                if(x<0)continue;
                mp[x].push_back({i,j});
            }
        }
    }
    int ans=1;
    for(auto [x,y]:mp){
        set<int> s;
        for(auto [u,v]:y){
            s.insert(u);
            s.insert(v);
        }
        ans=max(ans,(int)s.size());
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
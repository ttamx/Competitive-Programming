#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const bool dbg=false;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(n),cnt(m+n+1);
    vector<vector<pair<ll,ll>>> b(n);
    for(auto &x:a)cin >> x;
    ll ans=1ll*m*(m+1)*n;
    for(int i=1;i<=m;i++){
        ll p,v;
        cin >> p >> v;
        p--;
        b[p].emplace_back(i,v);
    }
    for(int i=0;i<n;i++){
        int pre=0;
        int val=a[i];
        b[i].emplace_back(m+1,0);
        for(auto [idx,v]:b[i]){
            cnt[val]+=idx-pre;
            pre=idx;
            val=v;
        }
    }
    for(int i=1;i<=n+m;i++){
        ans-=1ll*cnt[i]*(cnt[i]-1)/2;
        if(dbg)cerr << i << " " << cnt[i] << "\n";
    }
    if(dbg)cerr << "---------\n";
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
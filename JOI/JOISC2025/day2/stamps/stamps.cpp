#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=500005;
const ll INF=LLONG_MAX/2;

struct Fenwick{
    int t[N*4];
    void update(int i,int v){
        for(;i<N*4;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
    int query(int l,int r){
        return query(r)-query(l-1);
    }
}fl,fr;

int n,q;
ll sw;
int a[N*2];
ll c[N*2];
int l[N],r[N];
map<ll,ll> dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> sw;
    for(int i=1;i<=2*n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=2*n;i++){
        cin >> c[i];
    }
    ll cur=1LL*n*(n+1)/2;
    for(int i=1;i<=2*n;i++){
        if(l[a[i]]){
            r[a[i]]=i;
            cur+=fr.query(l[a[i]],i);
            fr.update(i,+1);
        }else{
            l[a[i]]=i;
            fl.update(i,+1);
        }
    }
    for(int i=1;i<=2*n;i++){
        if(dp.count(cur)){
            dp[cur]=min(dp[cur],c[i]);
        }else{
            dp[cur]=c[i];
        }
        fl.update(i,-1);
        fr.update(r[a[i]],-1);
        cur-=fl.query(i,r[a[i]]);
        l[a[i]]=r[a[i]];
        r[a[i]]=i+2*n;
        cur+=fr.query(l[a[i]],r[a[i]]);
        fl.update(l[a[i]],+1);
        fr.update(r[a[i]],+1);
    }
    cin >> q;
    ll best=INF;
    for(auto it=dp.end();it!=dp.begin();){
        it--;
        if(it->second>=best){
            it=dp.erase(it);
        }else{
            best=it->second;
        }
    }
    for(auto it=dp.begin();it!=dp.end();it++){
        auto it2=next(it);
        while(it2!=dp.end()&&it2->second>=it->second+(it2->first-it->first)*sw){
            it2=dp.erase(it2);
        }
    }
    dp[1LL*n*n+1]=INF;
    while(q--){
        ll k;
        cin >> k;
        auto it=dp.lower_bound(k);
        ll ans=it->second;
        if(it!=dp.begin()){
            auto [t,v]=*prev(it);
            ans=min(ans,v+(k-t)*sw);
        }
        cout << ans << "\n";
    }
}
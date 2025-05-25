#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=500005;
const ll INF=LLONG_MAX/2;

int n,q;
ll sw;
int a[N*4];
ll c[N];
int pos[N],cnt[N*4];
vector<pair<ll,int>> qr;
map<ll,ll> dp;

ll calc(int st){
    ll res=1LL*n*(n+1)/2;
    for(int i=1;i<=n;i++){
        pos[i]=0;
    }
    cnt[st-1]=0;
    for(int i=st;i<st+2*n;i++){
        cnt[i]=cnt[i-1];
        if(pos[a[i]]){
            res+=cnt[i]-cnt[pos[a[i]]];
            cnt[i]++;
        }else{
            pos[a[i]]=i;
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> sw;
    for(int i=1;i<=2*n;i++){
        cin >> a[i];
        a[i+2*n]=a[i];
    }
    for(int i=1;i<=2*n;i++){
        cin >> c[i];
    }
    for(int i=1;i<=2*n;i++){
        ll t=calc(i);
        if(dp.count(t)){
            dp[t]=min(dp[t],c[i]);
        }else{
            dp[t]=c[i];
        }
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
    dp[n*n+1]=INF;
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
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int INF=1e9;
const ll DEN=1e5;

int n,k;
ll a[N];
int dp[N];

struct PrefixMax{
    map<ll,int> mp;
    void update(ll i,int v){
        i=-i;
        auto it=mp.lower_bound(i);
        if(it!=mp.end()&&it->second>=v)return;
        it=mp.insert(it,{i,v});
        it->second=v;
        while(it!=mp.begin()&&(--it)->second<=v)it=mp.erase(it);
    }
    int query(ll i){
        i=-i;
        auto it=mp.lower_bound(i);
        return it==mp.end()?-INF:it->second;
    }
};

bool check(ll m){
    PrefixMax ds;
    ds.update(0,0);
    for(int i=1;i<=n;i++){
        ll cur=DEN*a[i]-i*m;
        dp[i]=ds.query(cur)+1;
        ds.update(cur,dp[i]);
    }
    return dp[n]>=k;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]+=a[i-1];
    }
    ll l=0,r=DEN*1000;
    while(l<r){
        ll m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << fixed << setprecision(5);
    cout << double(l)/DEN << "\n";
}
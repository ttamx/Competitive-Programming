#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=2e5+5;

ll n;

struct fenwick{
    ll t[N];
    void init(){
        for(ll i=1;i<=n+1;i++)t[i]=0;
    }
    void add(ll i,ll v){
        while(i<=n)t[i]+=v,i+=i&-i;
    }
    ll read(ll i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f,s;

void runcase(){
    ll k;
    cin >> n >> k;
    f.init();
    s.init();
    vector<ll> l(n),r(n);
    for(auto &x:l)cin >> x;
    for(auto &x:r)cin >> x;
    vector<pair<ll,ll>> v;
    for(ll i=0;i<n;i++)v.emplace_back(r[i]-l[i]+1,i);
    sort(v.rbegin(),v.rend());
    vector<ll> mp(n);
    for(ll i=0;i<n;i++)mp[v[i].second]=i+1;
    ll ans=1e18,sum=0;
    for(ll i=0;i<n;i++){
        f.add(mp[i],1);
        s.add(mp[i],r[i]-l[i]+1);
        sum+=r[i]-l[i]+1;
        if(sum<k)continue;
        ll lo=1,hi=n;
        while(lo<hi){
            ll m=(lo+hi)/2;
            if(s.read(m)>=k){
                hi=m;
            }else{
                lo=m+1;
            }
        }
        ans=min(ans,f.read(lo)*2+r[i]-(s.read(lo)-k));
    }
    if(ans==1e18)ans=-1;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll t(1);
    cin >> t;
    while(t--)runcase();
}
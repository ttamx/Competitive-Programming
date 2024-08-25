#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    ll k;
    cin >> n >> k;
    vector<pair<ll,int>> a(n);
    for(auto &x:a)cin >> x.first;
    for(auto &x:a)cin >> x.second;
    sort(a.begin(),a.end());
    int med=n/2;
    ll ans=0;
    for(int i=0;i<n;i++){
        if(i==med){
            med--;
        }
        if(a[i].second){
            ans=max(ans,a[i].first+a[med].first+k);
        }
    }
    ll val=a.back().first;
    auto check=[&](int x){
        int cnt=0;
        vector<int> v;
        for(int i=0;i<n-1;i++){
            if(a[i].first<x){
                cnt++;
                if(a[i].second){
                    v.emplace_back(a[i].first);
                }
            }
        }
        ll cost=0;
        while(cnt>(n-2)/2){
            if(v.empty())return false;
            cost+=x-v.back();
            v.pop_back();
            cnt--;
        }
        return cost<=k;
    };
    ll l=0,r=2e9;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    ans=max(ans,val+l);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
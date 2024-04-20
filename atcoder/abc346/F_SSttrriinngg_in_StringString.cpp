#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll k;
    cin >> k;
    string s,t;
    cin >> s >> t;
    int n=sz(s),m=sz(t);
    vector<vi> f(26,vi(n));
    for(int i=0;i<n;i++)f[s[i]-'a'][i]++;
    for(int i=0;i<26;i++)for(int j=1;j<n;j++)f[i][j]+=f[i][j-1];
    auto get=[&](int c,ll p){
        if(p<0)return 0LL;
        return (p/n)*f[c][n-1]+f[c][p%n];
    };
    auto check=[&](ll x){
        ll p=-1;
        for(auto c:t){
            ll l=p+1,r=k*n;
            while(l<r){
                ll m=(l+r)/2;
                if(get(c-'a',m)-get(c-'a',p)>=x)r=m;
                else l=m+1;
            }
            if(l>=k*n)return false;
            p=l;
        }
        return true;
    };
    ll l=0,r=k*n;
    while(l<r){
        ll m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l;
}
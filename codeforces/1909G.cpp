#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
vi prefix_function(const T& s){
    int n=sz(s);
    vi pi(n);
    for(int i=1,j=0;i<n;i++){
        while(j&&s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])j++;
        pi[i]=j;
    }
    return pi;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s >> t;
    int gap=m-n;
    int pre=0,suf=0;
    while(s[pre]==t[pre])pre++;
    while(s[n-suf-1]==t[m-suf-1])suf++;
    if(pre+suf<=n)cout << 0,exit(0);
    swap(pre,suf);
    pre=n-pre,suf=n-suf;
    string tmp(pre+all(t)-suf);
    n-=pre+suf,m-=pre+suf;
    int rt=m-prefix_function(tmp).back();
    ll ans=0;
    for(int len=1;len<=n;len++)if(gap%len==0&&len%rt==0)ans+=n-len+1;
    cout << ans;
}
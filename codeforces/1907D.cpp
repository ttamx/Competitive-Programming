#pragma once
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
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vi l(n),r(n);
    for(int i=0;i<n;i++)cin >> l[i] >> r[i];
    auto check=[&](int k){
        int pl=0,pr=0;
        for(int i=0,p=0;i<n;i++){
            pl=max(pl-k,l[i]);
            pr=min(pr+k,r[i]);
            if(pr<l[i]||r[i]<pl)return false;
        }
        return true;
    };
    int lo=0,hi=1e9;
    while(lo<hi){
        int m=(lo+hi)/2;
        if(check(m))hi=m;
        else lo=m+1;
    }
    cout << lo << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
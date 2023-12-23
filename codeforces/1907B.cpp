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
    vector<pair<int,char>> v[2];
    string s;
    cin >> s;
    for(int i=0;i<sz(s);i++){
        if(s[i]=='b'){
            if(!v[0].empty())v[0].pop_back();
        }else if(s[i]=='B'){
            if(!v[1].empty())v[1].pop_back();
        }else{
            v[isupper(s[i])].emplace_back(i,s[i]);
        }
    }
    for(auto x:v[1])v[0].emplace_back(x);
    sort(all(v[0]));
    for(auto [x,y]:v[0])cout << y;
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
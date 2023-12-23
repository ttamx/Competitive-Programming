#pragma once
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
template<class T>using maxheap=priority_queue<T>;
template<class T>using minheap=priority_queue<T,vector<T>,greater<T>>;
const int INF=0x3fffffff;
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));
#define overload3(a,b,c,name,...) name
#define overload4(a,b,c,d,name,...) name
#define rep1(n) for(ll _=0;_<n;_++)
#define rep2(i,n) for(ll i=0;i<n;i++)
#define rep3(i,a,b) for(ll i=a;i<b;i++)
#define rep4(i,a,b,c) for(ll i=a;i<b;i+=c)
#define rep(...) overload4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rrep1(i,n) for(ll i=n-1;i>=0;i--)
#define rrep2(i,a,b) for(ll i=a;i>b;i--)
#define rrep3(i,a,b,c) for(ll i=a;i>b;i-=c)
#define rrep(...) overload3(__VA_ARGS__,rrep3,rrep2,rrep1)(__VA_ARGS__)
#define sz(a) (int)(a).size()
#define all1(a) (a).begin(),(a).end()
#define all2(a,n) (a).begin(),(a).begin()+n
#define all3(a,l,r) (a).begin()+l,(a).begin()+r
#define all(...) overload3(__VA_ARGS__,all3,all2,all1)(__VA_ARGS__)
#define rall(a) (a).rbegin(),(a).rend()
#define sum(...) accumulate(all(__VA_ARGS__),0ll)
#define INT(...) int __VA_ARGS__;scan(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__;scan(__VA_ARGS__)
#define STR(...) string __VA_ARGS__;scan(__VA_ARGS__)
#define CHR(...) char __VA_ARGS__;scan(__VA_ARGS__)
#define DB(...) db __VA_ARGS__;scan(__VA_ARGS__)
#define VI(a,n) vi a(n);for(auto&&i:a)scan(i)
#define VL(a,n) vl a(n);for(auto&&i:a)scan(i)
#define VD(a,n) vd a(n);for(auto&&i:a)scan(i)
#define vv(t,a,n,...) vector<vector<t>> a(n,vi(__VA_ARGS__))
#define VV(t,a,n,m) vector<vector<t>> a(n,vector<t>(m));for(auto&&i:a)for(auto&&j:i)scan(j)
#define vvv(t,a,n,m,...) vector<vector<vector<t>>> a(n,vector<vector<t>>(m,vector<t>(__VA_ARGS__)))
template<class T>auto min(const T& a){return *min_element(all(a));}
template<class T>auto max(const T& a){return *max_element(all(a));}
template<class T,class U>bool chmin(T&a,const U&b){return a>T(b)?a=b,1:0;}
template<class T,class U>bool chmax(T&a,const U&b){return a<T(b)?a=b,1:0;}
template<class... T>void scan(T&... a){(cin >> ... >> a);}
template<class... T>void print(T... a){(cout << ... << a);}
void print(){cout << "\n";}
void YES(){print("YES\n");}
void NO(){print("NO\n");}
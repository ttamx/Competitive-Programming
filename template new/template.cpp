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
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class Fun>
class y_combinator_result{
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun):fun_(forward<T>(fun)){}
    template<class ...Args>
    decltype(auto) operator()(Args &&...args){return fun_(ref(*this), forward<Args>(args)...);}
};
template<class Fun>
decltype(auto) y_combinator(Fun &&fun){return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));}

void runcase(){
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
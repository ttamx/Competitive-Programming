#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m,k,p,q;
    cin >> n >> m >> k >> p >> q;
    p--,q--;
    vector<vector<ll>> s(n,vector<ll>(m));
    for(auto &v:s){
        for(auto &x:v){
            cin >> x;
        }
    }
    ll cur=s[p][q];
    priority_queue<tuple<ll,int,int>,vector<tuple<ll,int,int>>,greater<tuple<ll,int,int>>> pq;
    auto go=[&](int i,int j){
        if(i<0||i>=n||j<0||j>=m||s[i][j]==0)return;
        pq.emplace(s[i][j],i,j);
        s[i][j]=0;
    };
    s[p][q]=0;
    go(p-1,q);
    go(p,q-1);
    go(p,q+1);
    go(p+1,q);
    while(!pq.empty()){
        auto [v,i,j]=pq.top();
        pq.pop();
        if(v>(cur-1)/k)break;
        cur+=v;
        go(i-1,j);
        go(i,j-1);
        go(i,j+1);
        go(i+1,j);
    }
    cout << cur << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
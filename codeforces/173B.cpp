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
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<array<bool,2>>> vis(n,vector<array<bool,2>>(m));
    deque<tuple<int,int,int,int>> q;
    q.emplace_back(0,0,0,0);
    auto push=[&](int d,int i,int j,int s,bool b){
        if(i<0||i>=n||j<0||j>=m)return;
        if(b)q.emplace_back(d+1,i,j,s);
        else q.emplace_front(d,i,j,s);
    };
    while(!q.empty()){
        auto [d,i,j,s]=q.front();
        q.pop_front();
        if(vis[i][j][s])continue;
        vis[i][j][s]=true;
        if(i==n-1&&j==m-1&&!s){
            cout << d << "\n";
            return;
        }
        if(s){
            push(d,i-1,j,1,0);
            push(d,i+1,j,1,0);
            if(a[i][j]=='#'){
                push(d,i,j-1,0,1);
                push(d,i,j+1,0,1);
            }
        }else{
            push(d,i,j-1,0,0);
            push(d,i,j+1,0,0);
            if(a[i][j]=='#'){
                push(d,i-1,j,1,1);
                push(d,i+1,j,1,1);
            }
        }
    }
    cout << -1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
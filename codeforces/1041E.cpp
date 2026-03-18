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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    bool flag=true;
    vector<vector<int>> cnt(n);
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        if(y!=n)flag=false;
        cnt[x-1].emplace_back(i);
    }
    if(!flag)return void(cout << "NO\n");
    vector<pair<int,int>> ans(n-1);
    vector<int> nodes;
    for(int i=0;i<n;i++){
        if(cnt[i].empty()){
            nodes.emplace_back(i);
            continue;
        }
        int u=i;
        while(cnt[i].size()>1){
            if(nodes.empty())return void(cout << "NO\n");
            int v=nodes.back();
            nodes.pop_back();
            int j=cnt[i].back();
            cnt[i].pop_back();
            ans[j]={u,v};
            u=v;
        }
        ans[cnt[i][0]]={u,n-1};
    }
    cout << "YES\n";
    for(auto [u,v]:ans){
        cout << u+1 << " " << v+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
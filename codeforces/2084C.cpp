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
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    map<pair<int,int>,int> mp;
    vector<pair<int,int>> e;
    for(int i=0;i<n;i++){
        if(mp.count({b[i],a[i]}))e.emplace_back(mp[{b[i],a[i]}],i);
        else mp[{a[i],b[i]}]=i;
    }
    if(e.size()<n/2){
        cout << -1 << "\n";
    }else{
        vector<pair<int,int>> ne;
        vector<bool> vis(n);
        vector<int> tar(n,n/2);
        int c=0;
        for(auto [u,v]:e){
            tar[u]=c;
            tar[v]=n-c-1;
            c++;
        }
        vector<int> pos(n),val(n);
        for(int i=0;i<n;i++)pos[i]=val[i]=i;
        vector<pair<int,int>> ans;
        auto work=[&](int i,int j){
            assert(i!=j);
            swap(val[i],val[j]);
            swap(pos[val[i]],pos[val[j]]);
            ans.emplace_back(i,j);
        };
        for(int i=0;i<n;i++){
            if(pos[i]!=tar[i]){
                work(pos[i],tar[i]);
            }
        }
        cout << ans.size() << "\n";
        for(auto [u,v]:ans){
            cout << u+1 << " " << v+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
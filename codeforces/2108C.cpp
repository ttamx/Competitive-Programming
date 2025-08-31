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
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[-x].emplace_back(i);
    }
    vector<bool> ok(n),ok2(n),mark(n);
    function<void(int)> work=[&](int s){
        mark[s]=true;
        if(s>0){
            ok[s-1]=true;
            if(ok2[s-1]&&!mark[s-1]){
                work(s-1);
            }
        }
        if(s+1<n){
            ok[s+1]=true;
            if(ok2[s+1]&&!mark[s+1]){
                work(s+1);
            }
        }
    };
    int ans=0;
    for(auto &[_,v]:mp){
        for(auto i:v){
            ok2[i]=true;
        }
        for(auto i:v){
            if(ok[i]&&!mark[i]){
                work(i);
            }
        }
        for(auto i:v){
            if(!mark[i]){
                ans++;
                ok[i]=true;
                work(i);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.rbegin(),a.rend());
    if(a.size()>30){
        a.resize(30);
    }
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        int ans=0;
        priority_queue<int> pq;
        for(auto x:a){
            pq.emplace(x);
        }
        for(int b=29;b>=0;b--){
            if(!(x>>b&1))continue;
            if(pq.empty()){
                ans+=1<<b;
                continue;
            }
            auto v=pq.top();
            pq.pop();
            if(v<=(1<<b)){
                ans+=(1<<b)-v;
                continue;
            }
            pq.emplace(min(v-(1<<b),(1<<b)-1));
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
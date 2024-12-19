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
    int q;
    cin >> q;
    map<ll,bool> seen;
    map<ll,ll> ans;
    map<ll,vector<ll>> comp;
    map<ll,priority_queue<ll,vector<ll>,greater<ll>>> pq;
    seen[0]=true;
    while(q--){
        char op;
        ll x;
        cin >> op >> x;
        if(op=='+'){
            seen[x]=true;
        }else if(op=='-'){
            seen[x]=false;
            for(auto v:comp[x]){
                pq[v].emplace(x);
            }
        }else{
            if(pq.count(x)){
                while(!pq[x].empty()&&seen[pq[x].top()]){
                    pq[x].pop();
                }
                if(!pq[x].empty()){
                    cout << pq[x].top() << "\n";
                    continue;
                }
            }
            ll &cur=ans[x];
            while(seen[cur]){
                comp[cur].emplace_back(x);
                cur+=x;
            }
            cout << cur << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
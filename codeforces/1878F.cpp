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

const int X=1e6+5;
const ll LIM=2e6+5;

int lp[X];
int cnt[X];
int d=1;

void update(int x,int v){
    d/=cnt[x]+1;
    cnt[x]+=v;
    d*=cnt[x]+1;
}

void runcase(){
    int n,q;
    cin >> n >> q;
    for(int x=n;x>1;x/=lp[x]){
        update(lp[x],+1);
    }
    vector<ll> vals;
    vector<pair<int,int>> s;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int x;
            cin >> x;
            vals.emplace_back(x);
            for(;x>1;x/=lp[x]){
                update(lp[x],+1);
                s.emplace_back(lp[x],+1);
            }
            ll base=n%d;
            for(auto x:vals){
                base=base*x%d;
            }
            cout << (base==0?"YES":"NO") << "\n";
        }else{
            vals.clear();
            for(auto [x,v]:s){
                update(x,-v);
            }
            s.clear();
        }
    }
    for(auto [x,v]:s){
        update(x,-v);
    }
    for(int x=n;x>1;x/=lp[x]){
        update(lp[x],-1);
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<X;i++){
        if(lp[i])continue;
        for(int j=i;j<X;j+=i){
            if(!lp[j]){
                lp[j]=i;
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
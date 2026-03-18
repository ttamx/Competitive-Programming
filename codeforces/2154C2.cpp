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

const int N=2e5+5;
const int S=2000;

int lp[N];

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<ll> b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    ll ans=LINF;
    map<int,ll> cost;
    for(int i=0;i<n;i++){
        vector<pair<int,ll>> to_upd;
        for(int d=0;d<2;d++){
            int v=a[i]+d;
            while(v>1){
                int p=lp[v];
                while(v%p==0){
                    v/=p;
                }
                if(cost.count(p)){
                    ans=min(ans,d*b[i]+cost[p]);
                }
                to_upd.emplace_back(p,d*b[i]);
            }
        }
        for(auto [p,x]:to_upd){
            if(cost.count(p)){
                cost[p]=min(cost[p],x);
            }else{
                cost[p]=x;
            }
        }
    }
    int idx=min_element(b.begin(),b.end())-b.begin();
    for(int i=0;i<n;i++){
        if(i==idx){
            continue;
        }
        int v=a[i];
        while(v>1){
            int p=lp[v];
            while(v%p==0){
                v/=p;
            }
            ans=min(ans,b[idx]*((p-a[idx]%p)%p));
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(!lp[i]){
            for(int j=i;j<N;j+=i){
                if(!lp[j]){
                    lp[j]=i;
                }
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
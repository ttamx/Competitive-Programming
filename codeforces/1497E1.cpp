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

const int N=1e7+5;

int lp[N];
uint64_t hsh[N];

uint64_t get(int x){
    uint64_t res=0;
    while(x>1){
        int p=lp[x];
        res^=hsh[p];
        x/=p;
    }
    return res;
}

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<uint64_t> a(n);
    for(auto &x:a){
        int v;
        cin >> v;
        x=get(v);
    }
    int ans=0;
    for(int i=0;i<n;i++){
        ans++;
        set<uint64_t> s;
        int j=i;
        while(j<n&&s.emplace(a[j]).second)j++;
        i=j-1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(ll i=2;i<N;i++){
        if(lp[i])continue;
        hsh[i]=rng64();
        for(ll j=i;j<N;j+=i)if(!lp[j])lp[j]=i;
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
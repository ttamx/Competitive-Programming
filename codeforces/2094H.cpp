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

const int N=1e5+5;

vector<int> divisors[N];
vector<int> pos[N];

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    while(q--){
        int l,r,k;
        cin >> k >> l >> r;
        l--,r--;
        vector<int> b;
        for(auto d:divisors[k]){
            auto it=lower_bound(pos[d].begin(),pos[d].end(),l);
            if(it!=pos[d].end()&&*it<=r)b.emplace_back(*it);
        }
        sort(b.begin(),b.end());
        int last=l;
        ll ans=0;
        for(auto i:b){
            ans+=1LL*(i-last)*k;
            while(k%a[i]==0)k/=a[i];
            last=i;
        }
        ans+=1LL*(r-last+1)*k;
        cout << ans << "\n";
    }
    for(auto x:a)pos[x].clear();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}
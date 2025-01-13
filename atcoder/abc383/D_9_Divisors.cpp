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

const int N=2e6+5;

bool composite[N];

void runcase(){
    ll n;
    cin >> n;
    ll ans=0;
    for(int i=2;i<=100;i++){
        if(composite[i])continue;
        ll cur=1;
        for(int t=0;t<8;t++){
            cur*=i;
        }
        if(cur<=n){
            ans++;
        }
    }
    vector<ll> a;
    for(ll x=2;x*x<=n;x++){
        if(composite[x])continue;
        ll v=x*x;
        while(!a.empty()&&__int128_t(a.back())*v>n){
            a.pop_back();
        }
        ans+=a.size();
        a.emplace_back(v);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(!composite[i]){
            for(int j=2*i;j<N;j+=i){
                composite[j]=true;
            }
        }
    }
    int t(1);
    while(t--)runcase();
}
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
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<int> bad(10);
    vector<ll> coef(10);
    for(auto s:a){
        bad[s[0]-'a']=true;
        reverse(s.begin(),s.end());
        ll d=1;
        for(auto x:s){
            coef[x-'a']+=d;
            d*=10;
        }
    }
    ll ans=LINF;
    vector<int> b(10);
    iota(b.begin(),b.end(),0);
    do{
        if(bad[b[0]])continue;
        ll res=0;
        for(int i=0;i<10;i++){
            res+=coef[b[i]]*i;
        }
        ans=min(ans,res);
    }while(next_permutation(b.begin(),b.end()));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
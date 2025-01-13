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

int n,m,q;
ll a[N],b[N];
map<ll,bool> ans;
vector<ll> va,vb;
ll sa,sb;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sa+=a[i];
    }
    for(int i=1;i<=m;i++){
        cin >> b[i];
        sb+=b[i];
    }
    for(int i=1;i<=n;i++){
        if(sa!=a[i]){
            va.emplace_back(sa-a[i]);
        }
    }
    for(int i=1;i<=m;i++){
        if(sb!=b[i]){
            vb.emplace_back(sb-b[i]);
        }
    }
    sort(va.begin(),va.end());
    va.erase(unique(va.begin(),va.end()),va.end());
    sort(va.begin(),va.end(),[&](ll x,ll y){return abs(x)<abs(y);});
    while(!va.empty()&&abs(va.back())>=N)va.pop_back();
    sort(vb.begin(),vb.end());
    vb.erase(unique(vb.begin(),vb.end()),vb.end());
    sort(vb.begin(),vb.end(),[&](ll x,ll y){return abs(x)<abs(y);});
    while(!vb.empty()&&abs(vb.back())>=N)vb.pop_back();
    for(auto x:va){
        for(auto y:vb){
            if(abs(x*y)>=N)break;
            ans[x*y]=true;
        }
    }
    while(q--){
        int x;
        cin >> x;
        cout << (ans.count(x)?"YES":"NO") << "\n";
    }
}
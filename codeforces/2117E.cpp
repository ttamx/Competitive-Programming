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
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(int i=0;i<n;i+=2)swap(a[i],b[i]);
    int ans=0;
    map<int,int> pa,pb;
    for(int i=0;i<n;i++){
        if(a[i]==b[i])ans=max(ans,i+1);
        ans=max(ans,pb[a[i]]);
        ans=max(ans,pa[b[i]]);
        pa[a[i]]=i+1;
        pb[b[i]]=i+1;
    }
    pa.clear(),pb.clear();
    for(int i=2;i<n;i++){
        pa[a[i-2]]=i-1;
        pb[b[i-2]]=i-1;
        ans=max(ans,pa[a[i]]);
        ans=max(ans,pb[b[i]]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
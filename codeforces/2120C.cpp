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
    ll n,m;
    cin >> n >> m;
    if(m<n||m>n*(n+1)/2){
        cout << "-1\n";
        return;
    }
    m-=n;
    vector<int> a(n,-1);
    vector<bool> f(n);
    int cur=n;
    for(int i=0;i<n;i++){
        int pre=cur;
        if(cur==n-i)cur--;
        cur=min((ll)cur,m);
        m-=cur;
        if(cur!=pre){
            a[i]=cur;
            f[cur]=true;
        }
    }
    int val=n-1;
    for(int i=0;i<n;i++){
        while(val>=0&&f[val])val--;
        if(a[i]==-1){
            a[i]=val;
            val--;
        }
    }
    cout << a[0]+1 << "\n";
    for(int i=1;i<a.size();i++){
        cout << a[i-1]+1 << " " << a[i]+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
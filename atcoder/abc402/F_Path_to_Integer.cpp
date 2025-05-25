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
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> a(n,vector<ll>(n));
    for(auto &v:a)for(auto &x:v){
        cin >> x;
        x%=m;
    }
    vector<set<ll>> st(n);
    ll mul=1;
    for(int i=0;i<n-1;i++)mul=(mul*10)%m;
    for(int mask=0;mask<1<<(n-1);mask++){
        int i=0,j=0;
        ll cur=a[i][j];
        for(int s=0;s<n-1;s++){
            if(mask>>s&1)i++;
            else j++;
            cur=(cur*10+a[i][j])%m;
        }
        st[i].emplace((cur*mul)%m);
    }
    ll ans=0;
    for(int mask=0;mask<1<<(n-1);mask++){
        int i=n-1,j=n-1;
        ll cur=0,d=1;
        for(int s=0;s<n-1;s++){
            cur=(cur+a[i][j]*d)%m;
            if(mask>>s&1)i--;
            else j--;
            d=(d*10)%m;
        }
        auto it=st[i].lower_bound(m-cur);
        if(it!=st[i].begin())ans=max(ans,cur+*prev(it));
        if(!st[i].empty())ans=max(ans,(cur+*st[i].rbegin())%m);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
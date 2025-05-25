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
    vector<int> a[2],b[2];
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x>0)a[0].emplace_back(x);
        else a[1].emplace_back(-x);
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        if(x>0)b[0].emplace_back(x);
        else b[1].emplace_back(-x);
    }
    int ans=0;
    for(int t=0;t<2;t++){
        sort(a[t].begin(),a[t].end());
        sort(b[t].begin(),b[t].end());
        int i=0,j=0,k=0;
        vector<int> c(b[t].size()+1);
        for(int i=0;i<b[t].size();i++){
            auto it=lower_bound(a[t].begin(),a[t].end(),b[t][i]);
            c[i]=(it!=a[t].end()&&*it==b[t][i]);
            c[i]+=c[i+1];
        }
        int res=c[0];
        for(int i=0;i<b[t].size();i++){
            while(j<a[t].size()&&a[t][j]<=b[t][i]+j)j++;
            while(k<b[t].size()&&b[t][k]<b[t][i]+j)k++;
            res=max(res,k-i+c[k]);
        }
        ans+=res;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    int n,k,p;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    cin >> p;
    p--;
    int l=0,r=0;
    for(int i=p+1;i<n;i++)if(a[i]!=a[p]){
        int j=i;
        while(j+1<n&&a[j+1]==a[i]){
            j++;
        }
        l++;
        i=j;
    }
    for(int i=p-1;i>=0;i--)if(a[i]!=a[p]){
        int j=i;
        while(j>0&&a[j-1]==a[i]){
            j--;
        }
        r++;
        i=j;
    }
    cout << max(l,r)*2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
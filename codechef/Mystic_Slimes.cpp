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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> mn(n,vector<int>(n,INF)),mx(n,vector<int>(n,-INF));
    for(int i=0;i<n;i++){
        mn[i][i]=mx[i][i]=a[i];
    }
    for(int s=1;s<n;s++){
        for(int l=0,r=s;r<n;l++,r++){
            for(int m=l;m<r;m++){
                mn[l][r]=min({mn[l][r],mn[l][m]-mx[m+1][r],mn[m+1][r]-mx[l][m]});
                mx[l][r]=max({mx[l][r],mx[l][m]-mn[m+1][r],mx[m+1][r]-mn[l][m]});
            }
            mn[l][r]=max(mn[l][r],0);
            mx[l][r]=max(mx[l][r],0);
        }
    }
    cout << mx[0][n-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
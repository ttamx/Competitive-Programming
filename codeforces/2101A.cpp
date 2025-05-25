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
    vector<vector<int>> a(n,vector<int>(n));
    int cur=0;
    int i=(n-1)/2,j=(n-1)/2;
    for(int t=1;t<n;t++){
        if(t&1){
            j++;
            a[i][j]=++cur;
            for(int tt=0;tt<t;tt++)a[++i][j]=++cur;
            for(int tt=0;tt<t;tt++)a[i][--j]=++cur;
        }else{
            j--;
            a[i][j]=++cur;
            for(int tt=0;tt<t;tt++)a[--i][j]=++cur;
            for(int tt=0;tt<t;tt++)a[i][++j]=++cur;
        }
    }
    for(auto v:a){
        for(auto x:v)cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
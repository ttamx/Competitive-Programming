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
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    for(int s=0;s<n/2;s++){
        for(int t=0;t<(s+1)%4;t++){
            for(int i=s;i<n-s;i++){
                b[s][n-i-1]=a[i][s];
            }
            for(int i=s;i<n-s;i++){
                b[n-s-1][n-i-1]=a[i][n-s-1];
            }
            for(int i=s;i<n-s;i++){
                b[i][n-s-1]=a[s][i];
            }
            for(int i=s;i<n-s;i++){
                b[i][s]=a[n-s-1][i];
            }
            for(int i=s;i<n-s;i++){
                a[i][s]=b[i][s];
            }
            for(int i=s;i<n-s;i++){
                a[i][n-s-1]=b[i][n-s-1];
            }
            for(int i=s;i<n-s;i++){
                a[s][i]=b[s][i];
            }
            for(int i=s;i<n-s;i++){
                a[n-s-1][i]=b[n-s-1][i];
            }
        }
    }
    for(auto x:a){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
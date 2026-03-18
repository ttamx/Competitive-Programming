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
    int n,q;
    cin >> n >> q;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    array<int,3> c,d;
    for(int i=0;i<3;i++){
        c[i]=i;
        d[i]=0;
    }
    string s;
    cin >> s;
    for(auto x:s){
        if(x=='R')d[1]++;
        else if(x=='L')d[1]--;
        else if(x=='D')d[0]++;
        else if(x=='U')d[0]--;
        else if(x=='C'){
            swap(c[0],c[2]);
            swap(d[0],d[2]);
        }else if(x=='I'){
            swap(c[1],c[2]);
            swap(d[1],d[2]);
        }
    }
    vector<vector<int>> ans(n,vector<int>(n,-1));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            array<int,3> x{i,j,a[i][j]};
            ans[(x[c[0]]+d[0]%n+n)%n][(x[c[1]]+d[1]%n+n)%n]=(x[c[2]]+d[2]%n+n)%n;
        }
    }
    for(auto &v:ans){
        for(auto &x:v){
            cout << x+1 << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
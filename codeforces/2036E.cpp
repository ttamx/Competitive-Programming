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
    int n,k,q;
    cin >> n >> k >> q;
    vector<vector<int>> a(n,vector<int>(k));
    vector<vector<int>> b(k,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<k;j++){
            a[i][j]|=a[i-1][j];
        }
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            b[i][j]=a[j][i];
        }
    }
    while(q--){
        int m;
        cin >> m;
        int l=0,r=n-1;
        for(int i=0;i<m;i++){
            int x,c;
            char o;
            cin >> x >> o >> c;
            x--;
            if(o=='>'){
                int id=upper_bound(b[x].begin(),b[x].end(),c)-b[x].begin();
                l=max(l,id);
            }else{
                int id=lower_bound(b[x].begin(),b[x].end(),c)-b[x].begin()-1;
                r=min(r,id);
            }
        }
        cout << (l<=r?l+1:-1) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
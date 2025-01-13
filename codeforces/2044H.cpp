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

struct Matrix{
    int n;
    vector<vector<ll>> t;
    template<class F>
    Matrix(int _n,const F &f):n(_n),t(n,vector<ll>(n)){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                t[i][j]=f(i,j);
                if(i>0)t[i][j]+=t[i-1][j];
                if(j>0)t[i][j]+=t[i][j-1];
                if(i>0&&j>0)t[i][j]-=t[i-1][j-1];
            }
        }
    }
    ll query(int x1,int y1,int x2,int y2){
        ll res=t[x2][y2];
        if(x1>0)res-=t[x1-1][y2];
        if(y1>0)res-=t[x2][y1-1];
        if(x1>0&&y1>0)res+=t[x1-1][y1-1];
        return res;
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<vector<ll>> a(n,vector<ll>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    Matrix b(n,[&](int i,int j){return a[i][j];});
    Matrix c(n,[&](int i,int j){return a[i][j]*j;});
    Matrix d(n,[&](int i,int j){return a[i][j]*i;});
    while(q--){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--,y1--,x2--,y2--;
        ll vb=b.query(x1,y1,x2,y2);
        ll vc=c.query(x1,y1,x2,y2);
        ll vd=d.query(x1,y1,x2,y2);
        cout << vc-vb*y1+(vd-vb*x1)*(y2-y1+1)+vb << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
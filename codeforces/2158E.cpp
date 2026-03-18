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

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    int cnt=n*m;
    vector<vector<int>> deg(n,vector<int>(m));
    auto upd=[&](int i,int j,int v){
        if(deg[i][j]==0)cnt--;
        for(int d=0;d<4;d++){
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(ii<0||ii>=n||jj<0||jj>=m)continue;
            if(make_tuple(a[i][j],i,j)>make_tuple(a[ii][jj],ii,jj)){
                deg[i][j]+=v;
            }
        }
        if(deg[i][j]==0)cnt++;
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            upd(i,j,+1);
        }
    }
    cout << cnt << "\n";
    int q;
    cin >> q;
    while(q--){
        int i,j,x;
        cin >> i >> j >> x;
        i--,j--;
        upd(i,j,-1);
        for(int d=0;d<4;d++){
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(ii<0||ii>=n||jj<0||jj>=m)continue;
            upd(ii,jj,-1);
        }
        a[i][j]-=x;
        upd(i,j,+1);
        for(int d=0;d<4;d++){
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(ii<0||ii>=n||jj<0||jj>=m)continue;
            upd(ii,jj,+1);
        }
        cout << cnt << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
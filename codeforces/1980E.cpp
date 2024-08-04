#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vi> a(n,vi(m)),b(n,vi(m));
    for(auto &v:a)for(auto &x:v)cin >> x,x--;
    for(auto &v:b)for(auto &x:v)cin >> x,x--;
    vector<pii> pos(n*m);
    vi row(n),col(m),irow(n),icol(m);
    iota(all(row),0);
    iota(all(col),0);
    iota(all(irow),0);
    iota(all(icol),0);
    auto swaprow=[&](int i,int j){
        swap(row[i],row[j]);
        irow[row[i]]=i;
        irow[row[j]]=j;
    };
    auto swapcol=[&](int i,int j){
        swap(col[i],col[j]);
        icol[col[i]]=i;
        icol[col[j]]=j;
    };
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)pos[b[i][j]]=pii(i,j);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        int val=a[i][j];
        auto [x,y]=pos[val];
        int r=irow[x],c=icol[y];
        swaprow(i,r);
        swapcol(j,c);
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]!=b[row[i]][col[j]])return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
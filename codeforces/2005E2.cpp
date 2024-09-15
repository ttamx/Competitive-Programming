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

struct Fenwick{
    int t[1505][1505];
    int n,m;
    void init(int _n,int _m){
        n=_n,m=_m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                t[i][j]=0;
            }
        }
    }
    void update(int x,int y,int v){
        for(int i=x+1;i<=n;i+=i&-i){
            for(int j=y+1;j<=m;j+=j&-j){
                t[i][j]+=v;
            }
        }
    }
    int query(int x,int y){
        int res=0;
        for(int i=x+1;i>0;i-=i&-i){
            for(int j=y+1;j>0;j-=j&-j){
                res+=t[i][j];
            }
        }
        return res;
    }
}f;

void runcase(){
    int l,n,m;
    cin >> l >> n >> m;
    vector<int> a(l);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> b(n,vector<int>(m));
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
        }
        reverse(v.begin(),v.end());
    }
    reverse(b.begin(),b.end());
    vector<vector<pair<int,int>>> pos(n*m+1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            pos[b[i][j]].emplace_back(i,j);
        }
    }
    vector<int> cnt(n*m+1),cur(l);
    for(int i=0;i<l;i++){
        cnt[a[i]]++;
        cur[i]=cnt[a[i]];
    }
    f.init(n,m);
    vector<vector<pair<int,int>>> win(l+1);
    for(int t=l-1;t>=0;t--){
        if(cur[t]<=2){
            for(auto [i,j]:pos[a[t]]){
                if(i==0||j==0||f.query(i-1,j-1)==0){
                    win[t].emplace_back(i,j);
                }
            }
        }
        for(auto [i,j]:win[t+1]){
            f.update(i,j,-1);
        }
        for(auto [i,j]:win[t]){
            f.update(i,j,+1);
        }
    }
    cout << (f.query(n-1,m-1)>0?"T":"N") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
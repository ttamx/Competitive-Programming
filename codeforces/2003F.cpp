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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Fenwick{
    int n;
    vector<int> t;
    Fenwick(int n=0){init(n);}
    void init(int _n){
        n=_n;
        t.assign(n+1,-INF);
    }
    void update(int x,const int &v){
        for(int i=x+1;i<=n;i+=i&-i)t[i]=max(t[i],v);
    }
    int query(int x){
        int res=-INF;
        for(int i=x+1;i>0;i-=i&-i)res=max(res,t[i]);
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n),c(n);
    for(auto &x:a)cin >> x,x--;
    for(auto &x:b)cin >> x,x--;
    for(auto &x:c)cin >> x;
    vector<int> col(n);
    auto calc=[&](){
        int k=1<<m;
        vector<Fenwick> f(k,n);
        f[0].update(0,0);
        for(int i=0;i<n;i++){
            int x=1<<col[b[i]];
            for(int j=0;j<k;j++){
                if(j&x){
                    f[j].update(a[i],f[j^x].query(a[i])+c[i]);
                }
            }
        }
        return f[k-1].query(n-1);
    };
    int ans=-1;
    for(int i=0;i<400;i++){
        for(auto &x:col)x=rng()%m;
        ans=max(ans,calc());
    }
    cout << ans;
}
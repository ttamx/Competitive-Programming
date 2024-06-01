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

struct RMQ{
    int n;
    vi a;
    vector<vi> st;
    RMQ(const vi &b):n(sz(b)),a(b){
        st.assign(32-__builtin_clz(n),vi(n));
        for(int i=0;i<n;i++)st[0][i]=a[i];
        for(int i=1;i<sz(st);i++)for(int j=0;j+(1<<i)<=n;j++)st[i][j]=(st[i-1][j]|st[i-1][j+(1<<(i-1))]);
    }
    int query(int l,int r){
        int i=31-__builtin_clz(r-l+1);
        return (st[i][l]|st[i][r-(1<<i)+1]);
    }
};

const int K=1<<20;

map<int,int> f[K];

int query(int i,int idx){
    auto &x=f[i];
    auto it=x.upper_bound(idx);
    return it==x.begin()?INF:prev(it)->second;
}

void update(int i,int idx,int val){
    auto &x=f[i];
    if(val>=query(i,idx))return;
    x[idx]=val;
    for(auto it=x.upper_bound(idx);it!=x.end()&&val<=it->second;it=x.erase(it));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vi a(n),b(n),qs(n+1);
    for(int i=0;i<n;i++){
        a[i]=s[i]-'a';
        b[i]=1<<a[i];
        qs[i+1]=qs[i]^b[i];
    }
    RMQ seg(b);
    vi dp(n);
    update(0,-1,0);
    int mask=0;
    for(int i=0;i<n;i++){
        mask^=1<<a[i];
        int mask2=0;
        dp[i]=INF;
        for(int j=i;j>=0;){
            mask2=seg.query(j,i);
            dp[i]=min(dp[i],query(mask^mask2,j-1)+1);
            int l=-1,r=j-1;
            while(l<r){
                int m=(l+r+1)/2;
                if(seg.query(m,i)>mask2)l=m;
                else r=m-1;
            }
            j=l;
        }
        update(mask,i,dp[i]);
    }
    cout << dp[n-1];
}
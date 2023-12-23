#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    int n,m;
    vector<vi> t;
    RMQ(){}
    RMQ(const vi &a){init(a);}
    void init(const vi &a){
        n=sz(a),m=32-__builtin_clz(n);
        t.assign(m,vi(n));
        t[0]=a;
        for(int i=0;i<m-1;i++)for(int j=0;j+(2<<i)-1<n;j++)
            t[i+1][j]=min(t[i][j],t[i][j+(1<<i)]);
    }
    int query(int l,int r){
        if(r<l)return INF;
        int k=31-__builtin_clz(r-l+1);
        return min(t[k][l],t[k][r-(1<<k)+1]);
    }
};

struct suffixarray{
    vi sa,lcp,rank;
    suffixarray(){}
    suffixarray(const vi &s){init(s);}
    void init(const vi &s){
        int n=sz(s)+1;
        sa=lcp=rank=vi(n);
        iota(1+all(sa),0),sa[0]=n-1;
        sort(1+all(sa),[&](int a,int b){return s[a]<s[b];});
        for(int i=1;i<n;i++){
            int a=sa[i-1],b=sa[i];
            rank[b]=i>1&&s[a]==s[b]?rank[a]:i;
        }
        for(int k=1;k<n;k*=2){
            vi ps(sa),pr(rank),pos(n);
            iota(all(pos),0);
            for(auto i:ps)if((i-=k)>=0)sa[pos[rank[i]]++]=i;
            for(int i=1;i<n;i++){
                int a=sa[i-1],b=sa[i];
                rank[b]=pr[a]==pr[b]&&pr[a+k]==pr[b+k]?rank[a]:i;
            }
        }
        for(int i=0,j,k=0;i<n-1;lcp[rank[i++]]=k)
            for(k&&k--,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
    }
};

const int N=1e5+5;

int n,m,q;
int pos[N],sz[N];
vi a;
RMQ rmq;
suffixarray sa;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        pos[i]=sz(a);
        sz[i]=sz(s);
        for(auto x:s)a.emplace_back(x);
        a.emplace_back(-i);
    }
    sa.init(a);
    rmq.init(sa.lcp);
    m=sz(sa.sa);
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        int lcp=sz[x];
        x=sa.rank[pos[x]],y=sa.rank[pos[y]];
        if(x!=y){
            if(x>y)swap(x,y);
            lcp=rmq.query(x+1,y);
        }
        if(lcp==0){
            cout << "0\n";
            continue;
        }
        int ans=1;
        int l=1,r=x;
        while(l<r){
            int m=(l+r)/2;
            if(rmq.query(m+1,x)>=lcp)r=m;
            else l=m+1;
        }
        ans-=l;
        l=y,r=m-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(rmq.query(y+1,m)>=lcp)l=m;
            else r=m-1;
        }
        ans+=r;
        cout << ans << "\n";
    }
}
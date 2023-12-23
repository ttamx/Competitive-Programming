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
const int MOD=1000000007;
// const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

using vpi = vector<pii>;

struct RMQ{
    vector<vpi> t;
    void init(const vi &a){
        int n=sz(a),m=32-__builtin_clz(n);
        t.assign(m,vpi(n));
        for(int i=0;i<n;i++)t[0][i]=pii(a[i],i);
        for(int i=0;i<m-1;i++)for(int j=0;j+(2<<i)-1<n;j++)
            t[i+1][j]=min(t[i][j],t[i][j+(1<<i)]);
    }
    pii query(int l,int r){
        int k=__builtin_clz(r-l+1);
        return min(t[k][l],t[k][r-(1<<k)+1]);
    }
};

struct suffixarray{
    vi sa,lcp,rank;
    void init(const string &s){
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
            for(int i:ps)if((i-=k)>=0)sa[pos[rank[i]]++]=i;
            for(int i=1;i<n;i++){
                int a=sa[i-1],b=sa[i];
                rank[b]=pr[a]==pr[b]&&pr[a+k]==pr[b+k]?rank[a]:i;
            }
        }
        for(int i=0,j,k=0;i<n-1;lcp[rank[i++]]=k)
            for(k&&k--,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
    }
};

int n;
string a,b,c,s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b >> c;
    s=""
}
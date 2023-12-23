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

struct suffixarray{
    vi sa,lcp,rank;
    suffixarray(){}
    suffixarray(const string &s){init(s);}
    void init(const string &s){
        int n=sz(s)+1;
        sa=lcp=rank=vi(n);
        iota(1+all(sa),0),sa[0]=n-1;
        sort(1+all(sa),[&](int i,int j){return s[i]<s[j];});
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

void runcase(){
    string s;
    cin >> s;
    int n=sz(s);
    suffixarray sa(s);
    ll ans=1ll*n*(n+1)/2;
    for(auto x:sa.lcp)ans-=x;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
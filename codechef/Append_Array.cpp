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

const int N=2e6+5;
const int K=21;

bool ban[N];
vi dp[K];
int cnt[N];

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vi a(n);
    for(auto &x:a)cin >> x;
    ll sum=accumulate(all(a),0LL);
    int mx=0,mx2=0;
    for(auto x:a){
        mx2=max(mx2,cnt[x]);
        if(mx2>mx)swap(mx,mx2);
    }
    vl val(K,-INF),val2(K,-INF);
    for(int i=0;i<K;i++){
        auto it=upper_bound(all(dp[i]),m);
        if(it!=dp[i].begin())val[i]=val2[i]=*prev(it);
        if(i)val2[i]=max(val2[i],val2[i-1]);
    }
    ll ans=sum+val2[mx2]*k-mx-mx2;
    for(int i=mx2+1;i<=mx;i++){
        ll res=sum+val2[i]*k-i-mx;
        ans=max(ans,res);
    }
    for(int i=mx+1;i<K;i++){
        ll res=sum+max(val[i]+val2[mx]*(k-1)-i-mx,val[i]*2+val2[i]*(k-2)-2*i);
        ans=max(ans,res);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++)if(!ban[i]){
        for(int j=i;j<N;j+=i){
            ban[j]=true;
            int v=j;
            while(v%i==0)v/=i,cnt[j]++;
        }
    }
    for(int i=1;i<N;i++)dp[cnt[i]].emplace_back(i);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
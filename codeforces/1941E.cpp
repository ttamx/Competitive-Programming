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
    int n,m,k,d;
    cin >> n >> m >> k >> d;
    vector<vl> a(n,vl(m));
    for(auto &x:a)for(auto &y:x)cin >> y;
    vl val(n);
    ll ans=LINF,sum=0;
    for(int i=0;i<n;i++){
        vl dp(m);
        deque<int> dq;
        dq.emplace_back(0);
        dp[0]=1;
        for(int j=1;j<m;j++){
            while(!dq.empty()&&j-dq.front()>d+1)dq.pop_front();
            dp[j]=dp[dq.front()]+a[i][j]+1;
            while(!dq.empty()&&dp[dq.back()]>dp[j])dq.pop_back();
            dq.emplace_back(j);
        }
        val[i]=dp[m-1];
        sum+=val[i];
        if(i>=k-1){
            ans=min(ans,sum);
            sum-=val[i-k+1];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
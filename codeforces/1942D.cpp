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
    int n,k;
    cin >> n >> k;
    vector<vi> a(n+2,vi(n+2));
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)cin >> a[i][j];
    vector<vl> dp(n+2);
    dp[0].emplace_back(0);
    for(int i=1;i<=n;i++){
        priority_queue<pair<ll,int>> pq;
        vi ptr(n+2,1);
        pq.emplace(a[1][i],n+1);
        pq.emplace(dp[i-1][0],i-1);
        for(int j=0;j+2<=i;j++){
            pq.emplace(dp[j][0]+a[j+2][i],j);
        }
        while(!pq.empty()&&sz(dp[i])<k){
            auto [v,j]=pq.top();
            pq.pop();
            dp[i].emplace_back(v);
            if(ptr[j]<sz(dp[j])){
                pq.emplace(dp[j][ptr[j]++]+(j==i-1?0:a[j+2][i]),j);
            }
        }
    }
    for(auto x:dp[n])cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
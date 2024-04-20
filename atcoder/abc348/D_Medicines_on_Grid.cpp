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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    vector<vi> e(n,vi(m));
    for(auto &x:a)cin >> x;
    int k;
    cin >> k;
    for(int i=0;i<k;i++){
        int x,y,z;
        cin >> x >> y >> z;
        x--,y--;
        e[x][y]=max(e[x][y],z);
    }
    vector<vi> dp(n,vi(m,-1));
    priority_queue<tuple<int,int,int>> pq;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i][j]=='S'){
        dp[i][j]=e[i][j];
        pq.emplace(e[i][j],i,j);
    }
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(d<dp[i][j])continue;
        if(a[i][j]=='T')cout << "Yes",exit(0);
        if(d>0){
            d--;
            if(i>0&&a[i-1][j]!='#'&&max(d,e[i-1][j])>dp[i-1][j]){
                dp[i-1][j]=max(d,e[i-1][j]);
                pq.emplace(dp[i-1][j],i-1,j);
            }
            if(j>0&&a[i][j-1]!='#'&&max(d,e[i][j-1])>dp[i][j-1]){
                dp[i][j-1]=max(d,e[i][j-1]);
                pq.emplace(dp[i][j-1],i,j-1);
            }
            if(i+1<n&&a[i+1][j]!='#'&&max(d,e[i+1][j])>dp[i+1][j]){
                dp[i+1][j]=max(d,e[i+1][j]);
                pq.emplace(dp[i+1][j],i+1,j);
            }
            if(j+1<m&&a[i][j+1]!='#'&&max(d,e[i][j+1])>dp[i][j+1]){
                dp[i][j+1]=max(d,e[i][j+1]);
                pq.emplace(dp[i][j+1],i,j+1);
            }
        }
    }
    cout << "No";
}
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

const int N=305;
const int A=26;

int n,a;
string s;
int w[A][A],u[A];
ll dp[N][N][A][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> a;
    cin >> s;
    for(int i=0;i<26;i++)u[i]=INF;
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            cin >> w[i][j];
            u[i]=min(u[i],w[i][j]);
            u[j]=min(u[j],w[i][j]);
        }
    }
    for(int l=0;l<n;l++){
        for(int r=0;r<n;r++){
            for(int x=0;x<A;x++){
                dp[l][r][x][0]=dp[l][r][x][1]=LINF;
            }
        }
    }
    for(int i=0;i<n;i++){
        int c=s[i]-'a';
        for(int x=0;x<A;x++){
            dp[i][i][x][0]=w[c][x];
            dp[i][i][x][1]=w[c][x]+a;
        }
    }
    for(int l=0;l<n;l++){
        for(int r=l;r<n;r++){
            ll cost[2]={LINF,LINF};
            for(int x=0;x<26;x++){
                cost[0]=min(cost[0],dp[l][r][x][0]);
                cost[1]=min(cost[1],dp[l][r][x][1]);
                if(r+1<n){
                    if(s[r+1]==s[l]){
                        dp[l][r+1][x][1]=min(dp[l][r+1][x][1],dp[l][r][x][0]+a);
                    }
                    if(s[r+1]==s[r]){
                        dp[l][r+1][x][1]=min(dp[l][r+1][x][1],dp[l][r][x][1]);
                    }
                    if(s[r+1]-'a'==x){
                        dp[l][r+1][s[l]-'a'][1]=min(dp[l][r+1][x][1],dp[l][r][x][0]+a);
                        dp[l][r+1][s[r]-'a'][1]=min(dp[l][r+1][x][1],dp[l][r][x][1]);
                    }
                }
                if(l>0){
                    if(s[l-1]==s[l]){
                        dp[l][l-1][x][0]=min(dp[l][l-1][x][0],dp[l][r][x][0]);
                    }
                    if(s[l-1]==s[r]){
                        dp[l][l-1][x][0]=min(dp[l][l-1][x][0],dp[l][r][x][1]+a);
                    }
                    if(s[l-1]-'a'==x){
                        dp[l][l-1][s[l]-'a'][0]=min(dp[l][l-1][x][0],dp[l][r][x][0]);
                        dp[l][l-1][s[r]-'a'][0]=min(dp[l][l-1][x][0],dp[l][r][x][1]+a);
                    }
                }
            }
            if(r+1<n){
                for(int x=0;x<26;x++){
                    dp[l][r+1][x][1]=min(dp[l][r+1][x][1],cost[1]+w[s[r+1]-'a'][x]);
                }
            }
            if(l>0){
                for(int x=0;x<26;x++){
                    dp[l-1][r][x][0]=min(dp[l-1][r][x][0],cost[0]+w[s[l-1]-'a'][x]);
                }
            }
        }
    }
    ll ans=LINF;
    for(int x=0;x<26;x++){
        ans=min(ans,dp[0][n-1][x][0]);
        ans=min(ans,dp[0][n-1][x][1]);
    }
    cout << ans << "\n";
}
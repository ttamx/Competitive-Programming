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
    int n;
    cin >> n;
    vector<vector<int>> dd(n-1,vector<int>(n));
    vector<vector<int>> rr(n,vector<int>(n-1));
    for(auto &x:dd)for(auto &y:x)cin >> y;
    for(auto &x:rr)for(auto &y:x)cin >> y;
    int s1=2*(n-1)/3;
    int s2=2*(n-1)-s1;
    vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(n));
    function<void(int,int,int,ll)> dfs1=[&](int i,int j,int c,ll mask){
        if(c==s1){
            for(ll s=mask;s>0;s=(s-1)&mask){
                dp[i][j].emplace_back(s);
            }
            dp[i][j].emplace_back(0);
            return;
        }
        if(i+1<n){
            dfs1(i+1,j,c+1,mask|(1LL<<dd[i][j]));
        }
        if(j+1<n){
            dfs1(i,j+1,c+1,mask|(1LL<<rr[i][j]));
        }
    };
    dfs1(0,0,0,0LL);
    for(auto &x:dp){
        for(auto &v:x){
            sort(v.begin(),v.end());
            v.erase(unique(v.begin(),v.end()),v.end());
        }
    }
    int ans=0;
    function<void(int,int,int,ll)> dfs2=[&](int i,int j,int c,ll mask){
        if(c==s2){
            for(int s=ans+1;s<=2*n-2;s++){
                ll mask2=(~mask)&((1LL<<s)-1);
                auto it=lower_bound(dp[i][j].begin(),dp[i][j].end(),mask2);
                if(it!=dp[i][j].end()&&*it==mask2){
                    ans=s;
                }else{
                    break;
                }
            }
            return;
        }
        if(i>0){
            dfs2(i-1,j,c+1,mask|(1LL<<dd[i-1][j]));
        }
        if(j>0){
            dfs2(i,j-1,c+1,mask|(1LL<<rr[i][j-1]));
        }
    };
    dfs2(n-1,n-1,0,0LL);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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

void runcase(){
    int n,A,B;
    cin >> n >> A >> B;
    string s;
    cin >> s;
    vector dp(n+1,vector(n+1,vector(A,vector<bool>(B))));
    vector pre(n+1,vector(n+1,vector(A,vector<tuple<int,int,int>>(B))));
    dp[0][0][0][0]=true;
    for(int i=0;i<n;i++){
        int x=s[i]-'0';
        for(int j=0;j<=i;j++){
            for(int a=0;a<A;a++){
                for(int b=0;b<B;b++){
                    if(!dp[i][j][a][b])continue;
                    dp[i+1][j][a][(b*10+x)%B]=true;
                    pre[i+1][j][a][(b*10+x)%B]={j,a,b};
                    dp[i+1][j+1][(a*10+x)%A][b]=true;
                    pre[i+1][j+1][(a*10+x)%A][b]={j,a,b};
                }
            }
        }
    }
    pair<int,int> best(INF,-1);
    for(int i=1;i<n;i++){
        if(dp[n][i][0][0]){
            best=min(best,{abs(n-2*i),i});
        }
    }
    if(best.second!=-1){
        string ans(n,'B');
        for(int i=n,j=best.second,a=0,b=0;i>0;i--){
            int jj=j;
            tie(j,a,b)=pre[i][j][a][b];
            if(j!=jj)ans[i-1]='R';
        }
        cout << ans << "\n";
    }else{
        cout << "-1\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
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
    string s;
    cin >> s;
    vector<int> dp(n+1,0),last(n+1,-1);
    last[0]=0;
    int bal=0,cur=0;
    for(int i=1;i<=2*n;i++){
        bal+=(s[i-1]=='('?+1:-1);
        if(bal%2==1){
            last[bal/2]=-1;
        }
        if(last[bal]!=-1){
            dp[bal]+=i-last[bal];
        }
        cur=max(cur,dp[bal]);
        dp[bal]=cur;
        last[bal]=i;
    }
    cout << cur << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
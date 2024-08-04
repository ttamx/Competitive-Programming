#include<bits/stdc++.h>

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
    vector<int> cnt(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x-1]++;
    }
    vector<int> dp(n+1,INF);
    dp[0]=0;
    for(int i=0;i<n;i++)if(cnt[i]){
        vector<int> ndp(n+1,INF);
        for(int j=0;j<n;j++)ndp[j+1]=min(ndp[j+1],dp[j]+1);
        for(int j=cnt[i];j<=n;j++)ndp[j-cnt[i]]=min(ndp[j-cnt[i]],dp[j]);
        swap(dp,ndp);
    }
    cout << *min_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
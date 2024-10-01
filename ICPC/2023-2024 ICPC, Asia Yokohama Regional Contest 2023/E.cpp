#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=25;
const int B=1<<24;
const int MOD=998244353;

int n,m;
int a[N];
int dp[B];
vector<pair<int,int>> prq[N];

inline bool check(int mask,int i){
    for(auto [x,y]:prq[i]){
        if(((mask>>x&1)^(mask>>y&1))==0){
            return false;
        }
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin >> a >> b >> c;
        a--,b--,c--;
        prq[b].emplace_back(a,c);
    }
    int b=1<<n;
    dp[0]=1;
    for(int i=0;i<b;i++){
        for(int j=0;j<n;j++){
            if(i>>j&1)continue;
            int k=i|(1<<j);
            if(check(k,j)){
                dp[k]+=dp[i];
                if(dp[k]>=MOD)dp[k]-=MOD;
            }
        }
    }
    cout << dp[b-1];
}
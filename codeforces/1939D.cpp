#include<bits/stdc++.h>

using namespace std;

const int N=2005;

int n,sum;
int w[N];
unordered_map<int,int> dp[N][N];

int solve(int l,int r,int dt){
    if(l>r)return 0;
    auto it=dp[l][r].find(dt);
    if(it!=dp[l][r].end())return it->second;
    if(dt>=0){
        return dp[l]=max(w[l]+solve(l+1,r,dt-w[l]),w[r]+solve(l,r-1,dt-w[r]));
    }else{
        return dp[l]=min(solve(l+1,r,dt+w[l]),solve(l,r-1,dt+w[r]));
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> w[i],sum+=w[i];
    int res=solve(1,n,0);
    cout << res << " " << sum-res;
}
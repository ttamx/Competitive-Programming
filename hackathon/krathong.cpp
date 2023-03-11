#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2305;

int n;
vector<int> x,y;
pair<int,int> p[N];
ll dp[N][N];
ll ans;

ll calc(int a,int b,int c,int d){
    return dp[c][d]-dp[a-1][d]-dp[c][b-1]+dp[a-1][c-1];\
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        auto &[u,v]=p[i];
        cin >> u >> v;
        x.push_back(u);
        y.push_back(v);
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    for(int i=1;i<=n;i++){
        auto &[u,v]=p[i];
        u=lower_bound(x.begin(),x.end(),u)-x.begin()+1;
        v=lower_bound(x.begin(),x.end(),v)-x.begin()+1;
        dp[u][v]++;
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++){
        auto [a,b]=p[i];
        auto [c,d]=p[j];
        if(a>c)swap(a,c);
        if(b>d)swap(b,d);
        ans+=dp[][]
    }
    cout << ans;
}
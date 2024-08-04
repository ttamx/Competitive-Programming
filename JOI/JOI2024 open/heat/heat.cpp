#include<bits/stdc++.h>

using namespace std;

const int N=8005;
const int INF=INT_MAX/2;

int n,m;
int a[N],b[N],dp[N][4],qs[N];
vector<int> t[N];
int ans=0;

void chmax(int &x,int y){
    x=max(x,y);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    cin >> m;
    for(int i=1;i<=m;i++){
        int x;
        cin >> x;
        t[x].emplace_back(i);
    }
    for(int i=1;i<n;i++){
        while(t[i].size()>2){
            t[i].pop_back();
            ans++;
        }
    }
    if(n==2){
        cout << ans << "\n";
        return 0;
    }
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+t[i].size();
    for(int i=1;i<=n;i++)for(int j=0;j<4;j++)dp[i][j]=-INF;
    dp[1][0]=0;
    for(int i=2;i<n;i++){
        chmax(dp[i][(1<<t[i].size())-1],dp[i-1][(1<<t[i-1].size())-1]);
        for(int j=0;j<t[i].size();j++){
            int &x=dp[i][1<<j];
            vector<int> v;
            for(int k=i-1;i>0;k--){
                int mask=(1<<t[k].size())-1;
                for(int l=0;l<t[k].size();l++){
                    int cnt=max(0,v.size()-(i-k));
                    int y=dp[k][mask^(1<<l)];
                    chmax(x,y);
                    if()
                    chmax(x,y+max(0,qs[i-1]-qs[k]+2-(i-k)));
                }
                if(!t[k].empty())v.emplace_back([k][0]);
            }
        }
    }
    if(t[n-1].empty())ans+=dp[n-1][0];
    else{
        int res=0;
        for(int i=1;i<4;i++)res=max(res,dp[n-1][i]);
        ans+=res;
    }
    cout << ans << "\n";
}
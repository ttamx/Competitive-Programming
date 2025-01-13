#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

const int N=2e5+5;
const int M=1<<20;

int n,m;
int a[N];
pair<int,int> dp[M],dp2[M];

void update(int i,int x,int y){
    if(dp[i].second==y){
        dp[i].first=max(dp[i].first,x);
    }else{
        dp2[i]=max(dp2[i],make_pair(x,y));
        if(dp2[i]>dp[i]){
            swap(dp[i],dp2[i]);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<(1<<m);i++){
        dp[i]=dp2[i]={-INF,-INF};
    }
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        int mask=0;
        for(int j=0;j<m;j++){
            if(s[j]=='Y'){
                mask|=1<<j;
            }
        }
        a[i]=mask;
        update(mask,0,-i);
    }
    for(int i=0;i<m;i++){
        for(int u=0;u<(1<<m);u++){
            if(u>>i&1)continue;
            int v=u^(1<<i);
            update(u,dp[v].first+1,dp[v].second);
            update(u,dp2[v].first+1,dp2[v].second);
        }
    }
    tuple<int,int,int> ans(-1,-1,-1);
    for(int i=1;i<=n;i++){
        int mask=((1<<m)-1)^a[i];
        auto [val,idx]=dp[mask];
        if(-idx==i){
            tie(val,idx)=dp2[mask];
        }
        idx=-idx;
        if(idx!=INF){
            auto [x,y]=minmax(i,idx);
            ans=max(ans,make_tuple(val,-x,-y));
        }
    }
    if(get<0>(ans)==-1){
        cout << "No";
    }else{
        cout << -get<1>(ans) << " " << -get<2>(ans);
    }
}
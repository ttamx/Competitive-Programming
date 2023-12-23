#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=1<<19;
const int K=12;
const int inf=1e9;

int n;

struct segtree{
    int t[M];
    void build(int l,int r,int i){
        t[i]=-inf;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(0,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        t[i]=max(t[i],v);
        if(l==r)return;
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
    }
    void update(int x,int v){
        update(0,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return -inf;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(0,n,1,x,y);
    }
}s[K];

void runcase(){
    int m,k;
    cin >> n >> m >> k;
    for(int i=0;i<=k;i++)s[i].build();
    vector<vector<int>> add(n+2);
    vector<vector<int>> dp(n+2,vector<int>(k+2,-inf));
    for(int i=1;i<=m;i++){
        int l,r;
        cin >> l >> r;
        add[l].emplace_back(l);
        add[r+1].emplace_back(-l);
    }
    multiset<int> ms;
    for(int i=0;i<=k;i++){
        dp[0][i]=0;
        s[i].update(0,0);
    }
    for(int i=1;i<=n;i++){
        for(auto x:add[i]){
            if(x>0)ms.emplace(x);
            else ms.erase(ms.find(-x));
        }
        int p=0,cnt=ms.size();
        if(cnt>k)continue;
        for(auto l:ms){
            for(int j=cnt;j<=k;j++)dp[i][j]=max(dp[i][j],s[j-cnt].query(p,l-1)+1);
            p=l;
            cnt--;
        }
        for(int j=0;j<=k;j++)dp[i][j]=max(dp[i][j],s[j].query(p,i-1)+1);
        for(int j=0;j<=k;j++)s[j].update(i,dp[i][j]);
    }
    int ans=0;
    for(int i=0;i<=k;i++)ans=max(ans,s[i].t[1]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
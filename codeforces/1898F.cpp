#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;
typedef tuple<int,int,int,int> t4;
typedef tuple<int,int,int,int,int> t5;

const int inf=1e9;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<char>> g(n+2,vector<char>(m+2,'#'));
    p2 st;
    int sum=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        cin >> g[i][j];
        sum+=g[i][j]=='.';
        if(g[i][j]=='V')st=p2(i,j);
    }
    auto isempty=[&](int i,int j){
        return g[i][j]=='.';
    };
    vector<vector<int>> dp(n+2,vector<int>(m+2,inf));
    vector<t3> vec;
    auto gettype=[&](){
        vec.emplace_back(0,st.first,st.second);
        int cnt=0,mxd=0;
        auto go=[&](int d,int i,int j){
            if(isempty(i,j)){
                g[i][j]=',';
                vec.emplace_back(d+1,i,j);
            }
        };
        for(int v=0;v<vec.size();v++){
            auto [d,i,j]=vec[v];
            dp[i][j]=d;
            if(i==1||i==n||j==1||j==m){
                g[i][j]='E';
                cnt++,mxd=d;
            }
            go(d,i,j-1);
            go(d,i,j+1);
            go(d,i-1,j);
            go(d,i+1,j);
        }
        for(auto &x:g)for(auto &y:x)if(y==',')y='.';
        if(cnt==1)sum-=mxd;
        return min(cnt,2);
    };
    if(gettype()!=2)return void(cout << sum << "\n");
    vector<vector<p2>> dp1(n+2,vector<p2>(m+2,{inf,-1})),dp2(n+2,vector<p2>(m+2,{inf,-1}));
    int ans=inf;
    queue<t4> q;
    priority_queue<t5,vector<t5>,greater<t5>> pq;
    int idx=0;
    for(auto [d,i,j]:vec)if(g[i][j]=='E')q.emplace(0,++idx,i,j);
    auto go=[&](int d,int p,int i,int j){
        if(isempty(i,j)||g[i][j]=='V'){
            g[i][j]=',';
            q.emplace(d+1,p,i,j);
        }
    };
    while(!q.empty()){
        auto [d,p,i,j]=q.front();
        q.pop();
        dp1[i][j]={d,p};
        pq.emplace(d,0,p,i,j);
        go(d,p,i,j-1);
        go(d,p,i,j+1);
        go(d,p,i-1,j);
        go(d,p,i+1,j);
    }
    auto go2=[&](int d,int p,int i,int j){
        if(g[i][j]!='#'&&dp1[i][j].second!=p&&dp2[i][j].first>d+1){
            dp2[i][j]={d+1,p};
            pq.emplace(d+1,1,p,i,j);
        }
    };
    while(!pq.empty()){
        auto [d,t,p,i,j]=pq.top();
        pq.pop();
        ans=min(ans,dp[i][j]+dp1[i][j].first+dp2[i][j].first);
        go2(d,p,i,j-1);
        go2(d,p,i,j+1);
        go2(d,p,i-1,j);
        go2(d,p,i+1,j);
    }
    cout << sum-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
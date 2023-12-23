#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=105;
const int inf=2e9;

int n,k;
int a[N];
vector<p2> adj[N];
vector<int> dp[N][N];

void add(vector<int> &a,vector<int> b){
    vector<int> res(a.size()+b.size()-1,inf);
    for(int i=0;i<a.size();i++)for(int j=0;j<b.size();j++)res[i+j]=min(res[i+j],a[i]+b[j]);
    a=res;
}

void upd(vector<int> &a,vector<int> b){
    a.emplace_back(inf);
    for(int i=1;i<a.size();i++)a[i]=min(a[i],b[i-1]);
}

vector<int> sol(int st,int u,int d){
    if(!dp[st][u].empty())return dp[st][u];
    dp[st][u]={a[u]*d};
    for(auto [v,w]:adj[u])add(dp[st][u],sol(st,v,d+w));
    if(st!=u)upd(dp[st][u],sol(u,u,0));
    return dp[st][u];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1,m=n;i<=m;i++){
        int p,w;
        cin >> a[i] >> p >> w;
        adj[p].emplace_back(i,w);
    }
    cout << sol(0,0,0)[k];
}
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k;
long long dp[N];
vector<int> adj[N];
long long mx[N],s[N];

long long dfs(int u,long long k){
    if(k<=0)return 0;
    long long ret=s[u]*k;
    if(adj[u].size()==0)return ret;
    long long tmp=k/adj[u].size();
    k%=adj[u].size();
    vector<pair<long long,int>> mx;
    if(k>0){
        for(auto v:adj[u]){
            mx.emplace_back(dfs(v,tmp+1),v);
        }
        sort(mx.rbegin(),mx.rend());
        for(int i=0;i<k;++i){
            ret+=dfs(mx[i].second,tmp+1);
        }
        for(int i=k;i<adj[u].size();++i){
            ret+=dfs(mx[i].second,tmp);
        }
    }else{
        for(auto v:adj[u])ret+=dfs(v,tmp);
    }
    return ret;
}

void runcase(){
    cin >> n >> k;
    for(int i=1;i<=n;++i){
        adj[i].clear();
        mx[i]=s[i]=dp[i]=0;
    }
    for(int i=2;i<=n;++i){
        int x;
        cin >> x;
        adj[x].emplace_back(i);
    }
    for(int i=1;i<=n;++i)cin >> s[i];
    cout << dfs(1,k) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();   
}
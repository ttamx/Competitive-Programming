#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

int n;
int sz[N];
vector<int> adj[N];

template<int SZ=1>
ll knapsack(int n,vector<int> &vec){
    if(n>SZ)return knapsack<min(2*SZ,N)>(n,vec);
    vector<int> freq(n+1);
    for(auto x:vec)freq[x]++;
    bitset<SZ> dp;
    dp[0]=1;
    for(int i=1;i<=n;i++){
        if(freq[i]>2){
            int cnt=(freq[i]-1)/2;
            freq[i*2]+=cnt;
            freq[i]-=2*cnt;
        }
        for(int j=0;j<freq[i];j++)dp|=dp<<i;
    }
    ll res=0;
    for(int i=0;i<=n/2;i++)if(dp[i])res=max(res,1ll*i*(n-i));
    return res;
}

ll dfs(int u){
    ll sum=0;
    int ch=0;
    int maxsz=-1;
    sz[u]=1;
    vector<int> vec;
    for(auto v:adj[u]){
        sum+=dfs(v);
        sz[u]+=sz[v];
        ch+=sz[v];
        vec.emplace_back(sz[v]);
        maxsz=max(maxsz,sz[v]);
    }
    if(maxsz>=ch/2)return sum+1ll*(ch-maxsz)*maxsz;
    return sum+knapsack(ch,vec);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    cout << dfs(1);
}
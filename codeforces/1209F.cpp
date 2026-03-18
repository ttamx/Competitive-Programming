#include<bits/stdc++.h>

using namespace std;
using T = tuple<int,int,int,int,int>;

const int N=1e5+5;
const int M=N*15;
const int MOD=1e9+7;

int n,m,id;
vector<pair<int,int>> adj[M];
priority_queue<T,vector<T>,greater<T>> pq;
bool vis[M];
int ans[N];

void link(int u,int v,string s){
    for(int i=0;i+1<s.size();i++){
        id++;
        adj[u].emplace_back(id,s[i]-'0');
        u=id;
    }
    adj[u].emplace_back(v,s.back()-'0');
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    id=n;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        link(u,v,to_string(i));
        link(v,u,to_string(i));
    }
    int ord=0;
    pair<int,int> last(-1,-1);
    pq.emplace(0,0,0,0,1);
    while(!pq.empty()){
        auto [len,pre,suf,val,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        if(u<=n)ans[u]=val;
        if(make_pair(pre,suf)>last){
            last=make_pair(pre,suf);
            ord++;
        }
        for(auto [v,w]:adj[u])if(!vis[v]){
            pq.emplace(len+1,ord,w,(10LL*val+w)%MOD,v);
        }
    }
    for(int i=2;i<=n;i++){
        cout << ans[i] << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m,k,l;
    cin >> n >> m >> k >> l;
    vector<vector<int>> adj(n);
    vector<bool> f(n),ed(n);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        f[x-1]=true;
    }
    for(int i=0;i<l;i++){
        int x;
        cin >> x;
        ed[x-1]=true;
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> ord{0};
    vector<int> d(n,-1);
    d[0]=0;
    for(int i=0;i<ord.size();i++){
        int u=ord[i];
        for(auto v:adj[u])if(d[v]==-1){
            d[v]=d[u]+1;
            ord.emplace_back(v);
        }
    }
    vector<int> cnt(n);
    for(int i=0;i<n;i++)if(f[i])cnt[d[i]]++;
    if(*max_element(cnt.begin(),cnt.end())>1){
        cout << string(n-1,'0') << "\n";
        return;
    }
    vector<bool> pre(n),suf(n);
    for(auto u:ord){
        if(cnt[d[u]]&&!f[u])continue;
        if(!u){
            pre[u]=true;
            continue;
        }
        for(auto v:adj[u]){
            if(pre[v]&&d[v]+1==d[u]){
                pre[u]=true;
                break;
            }
        }
    }
    int st=n-1;
    while(st>=0&&!cnt[st])st--;
    reverse(ord.begin(),ord.end());
    for(auto u:ord){
        if(cnt[d[u]]&&!f[u])continue;
        if(ed[u]&&d[u]>=st){
            suf[u]=true;
            continue;
        }
        for(auto v:adj[u]){
            if(suf[v]&&d[u]+1==d[v]){
                suf[u]=true;
                break;
            }
        }
    }
    string ans(n-1,'0');
    for(int i=1;i<n;i++){
        if(pre[i]&&suf[i]&&(f[i]||!cnt[d[i]])){
            ans[i-1]='1';
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
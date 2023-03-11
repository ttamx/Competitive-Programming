#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;
const int N=2e5+5;
const int M=4e5+5;

int n,m,cnt;
int a[N],ans[N];
map<pair<int,int>,int> mp;
pair<int,int> p[M];
int idx=0;
vector<int> v[N];
vector<int> adj[M];
queue<int> q;
bool vis[M];
int nxt[M],suf[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)ans[i]=2e9;
    p[++cnt]={1,0};
    mp[{1,0}]=cnt;
    v[1].emplace_back(0);
    for(int i=0;i<m;i++){
        int c,r,d,s;
        cin >> c >> r >> d >> s;
        v[c].emplace_back(r);
        v[d].emplace_back(s);
        if(mp[{c,r}]==0){
            p[++cnt]={c,r};
            mp[{c,r}]=cnt;
        }
        if(mp[{d,s}]==0){
            p[++cnt]={d,s};
            mp[{d,s}]=cnt;
        }
        adj[mp[{c,r}]].emplace_back(mp[{d,s}]);
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sort(v[i].begin(),v[i].end());
        v[i].erase(unique(v[i].begin(),v[i].end()),v[i].end());
        for(int j=0;j+1<v[j].size();j++)suf[mp[{i,v[i][j]}]]=mp[{i,v[i][j+1]}];
    }
    for(int i=1;i<=cnt;i++){
        auto [x,y]=p[i];
        auto it=lower_bound(v[x].begin(),v[x].end(),y+a[x]);
        if(it!=v[x].end())nxt[i]=mp[{x,*it}];
        if(DBG)cerr << "(" << p[i].first << "," << p[i].second << ") -> (" << p[nxt[i]].first << "," << p[nxt[i]].second << ")\n";
    }
    q.emplace(1);
    vis[0]=vis[1]=true;
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        ans[p[u].first]=min(ans[p[u].first],p[u].second);
        if(DBG)cerr << "(" << p[u].first << "," << p[u].second << ") : ";
        for(auto nx:adj[u]){
            ans[p[nx].first]=min(ans[p[nx].first],p[nx].second);
            nx=nxt[nx];
            if(vis[nx])continue;
            q.emplace(nx);
            vis[nx]=true;
            if(DBG)cerr << "(" << p[nx].first << "," << p[nx].second << ") ";
        }
        if(!vis[suf[u]]){
            q.emplace(suf[u]);
            vis[suf[u]]=true;
            if(DBG)cerr << "(" << p[suf[u]].first << "," << p[suf[u]].second << ") ";
        }
        if(DBG)cerr << "\n";
    }
    for(int i=1;i<=n;i++){
        cout << (ans[i]==2e9?-1:ans[i]) << '\n';
    }
}
#include<bits/stdc++.h>

using namespace std;

using P = pair<int,int>;

struct Hopkroft{
    int n,m;
    vector<int> match,lv,ptr;
    vector<vector<int>> adj;
    Hopkroft(int n,int m):n(n),m(m),adj(n){}
    void add_edge(int u,int v){
        adj[u].emplace_back(v+n);
    }
    void bfs(){
        lv.assign(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++)if(match[i]==-1){
            lv[i]=0;
            q.emplace(i);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u])if(match[v]!=-1&&lv[match[v]]==-1){
                lv[match[v]]=lv[u]+1;
                q.emplace(match[v]);
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(match[v]==-1||(lv[match[v]]==lv[u]+1&&dfs(match[v]))){
                match[u]=v;
                match[v]=u;
                return true;
            }
        }
        return false;
    }
    int solve(){
        int ans=0,cnt=0;
        match.assign(n+m,-1);
        do{
            ptr.assign(n,0);
            bfs();
            cnt=0;
            for(int i=0;i<n;i++)if(match[i]==-1&&dfs(i))cnt++;
            ans+=cnt;
        }while(cnt);
        return ans;
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<tuple<int,int,int>>> event(n);
    vector<int> vals;
    for(int i=0;i<m;i++){
        int t,l,r,k;
        cin >> t >> l >> r >> k;
        t--,l--,r--;   
        event[l].emplace_back(t,r,k);
        vals.emplace_back(k);
    }
    sort(vals.begin(),vals.end());
    priority_queue<P> pqmn;
    priority_queue<P,vector<P>,greater<P>> pqmx;
    pqmn.emplace(-1,n);
    pqmx.emplace(m,n);
    vector<int> ans(n);
    Hopkroft bm(n,m);
    for(int i=0;i<n;i++){
        while(pqmn.top().second<i)pqmn.pop();
        while(pqmx.top().second<i)pqmx.pop();
        for(auto [t,r,k]:event[i]){
            k=lower_bound(vals.begin(),vals.end(),k)-vals.begin();
            if(t)pqmx.emplace(k,r);
            else pqmn.emplace(k,r);
        }
        int lo=pqmn.top().first,hi=pqmx.top().first;
        if(lo>hi){
            cout << -1 << "\n";
            return;
        }
        if(lo>=0){
            bm.add_edge(i,lo);
            ans[i]=vals[lo];
        }
        if(hi<m){
            bm.add_edge(i,hi);
            ans[i]=vals[hi];
        }
    }
    if(bm.solve()!=m){
        cout << -1 << "\n";
        return;
    }
    for(int i=0;i<n;i++){
        if(bm.match[i]!=-1)ans[i]=vals[bm.match[i]-n];
        cout << ans[i] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
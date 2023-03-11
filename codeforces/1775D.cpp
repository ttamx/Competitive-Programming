#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int K=650;

void runcase(){
    vector<bool> notprime(K);
    vector<int> prime;
    for(int i=2;i<K;i++){
        if(notprime[i])continue;
        prime.push_back(i);
        for(int j=i;j<K;j+=i)notprime[j]=true;
    }
    int n;
    cin >> n;
    vector<int> a(n+1);
    vector<vector<pair<int,int>>> adj(N);
    for(int i=1;i<=n;i++){
        auto &x=a[i];
        cin >> x;
        int num=x;
        vector<int> res;
        for(auto p:prime){
            if(num%p)continue;
            res.push_back(p);
            while(num%p==0)num/=p;
        }
        if(num>1)res.push_back(num);
        for(auto u:res)for(auto v:res)if(u!=v)adj[u].push_back({v,i});
    }
    int s,t;
    cin >> s >> t;
    if(s==t){
        cout << 1 << '\n';
        cout << s << '\n';
        return;
    }
    vector<pair<int,int>> pa(N);
    vector<bool> des(N),vis(N);
    queue<int> q;
    int num=a[s];
    for(auto p:prime){
        if(num%p)continue;
        q.push(p),pa[p]={0,s},vis[p]=true;
        while(num%p==0)num/=p;
    }
    if(num>1)q.push(num),pa[num]={0,s},vis[num]=true;
    num=a[t];
    for(auto p:prime){
        if(num%p)continue;
        des[p]=true;
        while(num%p==0)num/=p;
    }
    if(num>1)des[num]=true;
    int cur=-1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(des[u]){
            cur=u;
            break;
        }
        for(auto [v,w]:adj[u]){
            if(vis[v])continue;
            q.push(v);
            vis[v]=true;
            pa[v]={u,w};
        }
    }
    if(cur==-1){
        cout << -1;
        return;
    }
    vector<int> ans;
    ans.push_back(t);
    while(cur){
        auto [u,w]=pa[cur];
        ans.push_back(w);
        cur=u;
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for(auto x:ans)cout << x << ' ';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
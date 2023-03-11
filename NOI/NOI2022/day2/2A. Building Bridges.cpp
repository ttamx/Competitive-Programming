#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<long long,int,int> t3;

const int N=1e5+5;

int n,m,q,req;
long long ans;
long long h[N];
int p[N],pa[N];
bool used[N];
set<int> s;
vector<p2> v,ANS;
queue<p2> ch[N];
priority_queue<t3,vector<t3>,greater<t3>> pq;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    int mn=2e9,root;
    for(int i=1;i<=n;++i){
        cin >> h[i];
        p[i]=i;
        v.emplace_back(h[i],i);
        if(h[i]<mn){
            mn=h[i];
            root=i;
        }
    }
    for(int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        u=fp(u),v=fp(v);
        if(u!=v)p[v]=u;
    }
    for(int i=1;i<=n;++i)pa[i]=fp(i);
    sort(v.begin(),v.end());
    for(auto [w,i]:v)ch[pa[i]].emplace(h[i],i);
    set<p2> s;
    for(int i=1;i<=n;++i){
        if(!ch[i].empty())s.insert(ch[i].front()),++req;
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i==j)continue;
            pq.emplace(h[i]+h[j],i,j);
        }
    }
    while(!pq.empty()){
        auto [w,u,v]=pq.top();
        pq.pop();
        if(used[u]||used[v])continue;
        if(fp(u)==fp(v))continue;
        used[u]=used[v]=true;
        p[fp(u)]=fp(v);
        ans+=w;
        ANS.emplace_back(u,v);
    }
    for(int i=1;i<=n;++i){
        if(fp(i)!=fp(1)){
            cout << -1;
            return 0;
        }
    }
    /*
    for(auto [w,i]:v){
        if(used[i])continue;
        used[i]=true;
        ch[pa[i]].pop();
        s.erase(s.begin());
        if(!ch[pa[i]].empty())s.insert(ch[pa[i]].front());
        auto it=s.begin();
        while(it!=s.end()&&fp(it->second)==fp(i))it++;
        if(it==s.end())break;
        int u=it->second;
        ANS.emplace_back(i,u);
        ans+=it->first+w;
        used[u]=true;
        p[fp(i)]=fp(u);
        u=pa[u];
        ch[u].pop();
        s.erase(it);
        if(!ch[u].empty())s.insert(ch[u].front());
    }
    */
    if(ANS.size()<req-1){
        cout << -1;
        return 0;
    }
    cout << ans << '\n';
    if(q==1){
        cout << ANS.size() << '\n';
        for(auto [u,v]:ANS)cout << u << ' ' << v << '\n';
    }
}
/*
15 15 1
1 6 9 1 6 10 2 6 8 1 7 10 3 4 5
1 2
2 3
1 3
4 6
5 6
4 5
7 9
7 8
8 9
10 12
11 12
10 11
13 14
13 15
14 15

*/

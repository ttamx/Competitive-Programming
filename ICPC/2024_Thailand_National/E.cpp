#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,n;
    cin >> m >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    stack<int> s;
    int rt=-1;
    vector<int> l(n,-1),r(n,-1),sz(n);
    for(int i=0;i<n;i++){
        while(!s.empty()&&a[s.top()]<a[i]){
            l[i]=s.top();
            s.pop();
        }
        if(s.empty()){
            rt=i;
        }else{
            r[s.top()]=i;
        }
        s.emplace(i);
    }
    vector<pair<int,int>> b;
    function<void(int,int)> dfs=[&](int u,int p){
        if(u==-1)return;
        dfs(l[u],a[u]);
        dfs(r[u],a[u]);
        sz[u]=1;
        if(l[u]!=-1)sz[u]+=sz[l[u]];
        if(r[u]!=-1)sz[u]+=sz[r[u]];
        b.emplace_back(sz[u],p-a[u]);
    };
    dfs(rt,m);
    long long ans=0;
    int cur=m;
    sort(b.rbegin(),b.rend());
    for(auto [x,y]:b){
        int used=min(cur,y);
        cur-=used;
        ans+=1LL*used*x;
    }
    cout << ans;
}
#include<bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> t3;

const int N=1e5+5;

int n,m,t;
int p[N];
priority_queue<t3,vector<t3>,greater<t3>> pq;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m;
        iota(p,p+n+1,0);
        int ans=1;
        while(m--){
            int u,v;
            long long w;
            cin >> u >> v >> w;
            pq.emplace(log2l(w),u,v);
        }
        while(!pq.empty()){
            auto [w,u,v]=pq.top();
            pq.pop();
            u=fp(u),v=fp(v);
            if(u==v)continue;
            p[u]=v;
            ans+=w;
        }
        cout << ans << '\n';
    }
}
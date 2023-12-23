#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=2e5+5;

struct DSU{
    vector<int> p;
    void init(int n){
        p.resize(n+1);
        iota(p.begin(),p.end(),0);
    }
    int fp(int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    }
    bool uni(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        p[v]=u;
        return true;
    }
}dsu;

int n,k;
map<int,vector<int>> mp;
priority_queue<t3,vector<t3>,greater<t3>> pq;
int ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    dsu.init(n);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        mp[x].emplace_back(i);
    }
    for(auto [x,v]:mp){
        int p=v[0];
        for(auto i:v)dsu.uni(p,i);
        pq.emplace(v.size(),1,p);
    }
    while(pq.size()>1){
        auto [f1,d1,u1]=pq.top();
        pq.pop();
        bool ok1=false,ok2=false;
        int sum=f1;
        while(!pq.empty()){
            auto [f2,d2,u2]=pq.top();
            if(f1!=f2||d1!=d2||d2>=k)break;
            sum+=f2;
            dsu.uni(u1,u2);
            pq.pop();
            ok1=true;
        }
        if(!ok1){
            while(!pq.empty()){
                auto [f2,d2,u2]=pq.top();
                if(f1!=f2||d2>=k)break;
                if(ok2&&d1!=d2)break;
                d1=d2;
                sum+=f2;
                dsu.uni(u1,u2);
                pq.pop();
                ok2=true;
            }
        }
        if(ok1||ok2){
            pq.emplace(sum,d1+1,u1);
        }else{
            ans[dsu.fp(u1)]=f1;
        }
    }
    auto [f,d,u]=pq.top();
    ans[dsu.fp(u)]=f;
    for(int i=1;i<=n;i++)cout << ans[dsu.fp(i)] << " \n"[i==n];
}
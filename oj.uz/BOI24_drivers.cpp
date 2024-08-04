#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,q;
int p[N];
vector<tuple<int,int,int>> a;
vector<tuple<int,int,int,int>> qr;
bool ans[N];

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    a.resize(m);
    for(auto &[w,u,v]:a)cin >> u >> v >> w;
    for(int i=0;i<q;i++){
        int u,v,w;
        cin >> u >> v >> w;
        qr.emplace_back(w,u,v,i);
    }
    sort(a.rbegin(),a.rend());
    sort(qr.begin(),qr.end());
    iota(p,p+n+1,0);
    for(auto [w,u,v,i]:qr){
        while(!a.empty()&&get<0>(a.back())<=w){
            auto [w,u,v]=a.back();
            a.pop_back();
            p[fp(u)]=fp(v);
        }
        ans[i]=fp(u)==fp(v);
    }
    for(int i=0;i<q;i++)cout << (ans[i]?"TAIP":"NE") << "\n";
}
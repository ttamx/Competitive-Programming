#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,q;
int p[N],col[N];
bool ok[N];
vector<int> comp[N];
int ans=0;
vector<int> vec;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

void link(int u,int v){
    int pu=fp(u),pv=fp(v);
    if(pu==pv){
        if(col[u]==col[v])ok[pu]=true;
        return;
    }
    if(comp[pu].size()<comp[pv].size()){
        swap(u,v);
        swap(pu,pv);
    }
    if(col[u]==col[v]){
        for(auto i:comp[pv])col[i]^=1;
    }
    for(auto i:comp[pv])comp[pu].emplace_back(i);
    comp[pv].clear();
    ok[pu]|=ok[pv];
    p[pv]=pu;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        p[i]=i;
        comp[i].emplace_back(i);
    }
    while(m--){
        int u,v;
        cin >> u >> v;
        link(u,v);
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int a,b,c,p,v;
            cin >> a >> b >> c >> p >> v;
            p=fp(p);
            if(fp(a)==p&&fp(b)==p&&fp(c)==p&&(ok[p]||(col[a]==col[b]&&col[a]==col[c]))){
                vec.emplace_back(v);
            }else{
                vec.emplace_back(0);
            }
        }else{
            int u,v;
            cin >> u >> v;
            link(u,v);
        }
    }
    sort(vec.rbegin(),vec.rend());
    for(auto x:vec)cout << (ans+=x) << "\n";
}
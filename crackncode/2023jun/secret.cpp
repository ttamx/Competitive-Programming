#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,q;
int pa[N],sz[N];
bool ok[N],col[N];
vector<int> vec;

int fp(int u){
    if(u==pa[u])return u;
    return fp(pa[u]);
}

bool getcol(int u){
    if(u==pa[u])return col[u];
    return col[u]^getcol(pa[u]);
}

void add(int u,int v){
    int pu=fp(u),pv=fp(v);
    if(pu==pv){
        if(getcol(u)==getcol(v)){
            ok[pu]=true;
        }
    }else{
        if(getcol(u)==getcol(v)){
            col[pv]^=true;
        }
        if(sz[pv]>sz[pu])swap(pu,pv);
        pa[pv]=pu;
        sz[pu]+=sz[pv];
        ok[pu]|=ok[pv];
        col[pv]^=col[pu];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)pa[i]=i,sz[i]=1;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y,z,p,v;
            cin >> x >> y >> z >> p >> v;
            int px=fp(x),py=fp(y),pz=fp(z),pp=fp(p);
            if(px!=py||py!=pz||pz!=pp){
                vec.emplace_back(0);
                continue;
            }
            if(ok[pp]){
                vec.emplace_back(v);
                continue;
            }
            int cx=getcol(x),cy=getcol(y),cz=getcol(z);
            if(cx==cy&&cy==cz){
                vec.emplace_back(v);
            }else{
                vec.emplace_back(0);
            }
        }else{
            int u,v;
            cin >> u >> v;
            add(u,v);
        }
    }
    sort(vec.rbegin(),vec.rend());
    for(int i=1;i<vec.size();i++)vec[i]+=vec[i-1];
    for(auto x:vec)cout << x << "\n";
}
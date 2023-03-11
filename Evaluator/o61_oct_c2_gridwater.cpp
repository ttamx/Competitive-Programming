#include<bits/stdc++.h>

using namespace std;

const int N=16e4+5;

int m,n;
int p[N],l[N],r[N];
vector<tuple<int,int,int>> edge,mst,nonmst;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

int calc(int x,int y){
    return x*400+y;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=1;i<2*m;++i){
        if(i&1){
            for(int j=1;j<n;++j){
                int x;
                cin >> x;
                int u=calc(i/2,j-1),v=calc(i/2,j);
                edge.emplace_back(x,u,v);
            }
        }else{
            for(int j=0;j<n;++j){
                int x;
                cin >> x;
                int u=calc(i/2,j),v=calc(i/2-1,j);
                edge.emplace_back(x,u,v);
            }
        }
    }
    sort(edge.begin(),edge.end());
    iota(p,p+N,0);
    for(auto it:edge){
        auto [w,u,v]=it;
        u=fp(u),v=fp(v);
        if(u!=v){
            p[u]=v;
            mst.emplace_back(it);
        }else{
            nonmst.emplace_back(it);
        }
    }
    for(int i=0;i<nonmst.size();++i){
        l[i]=0;
        r[i]=mst.size()-1;
    }
    while(true){
        bool done=true;
        vector<vector<int>> res(mst.size());
        for(int i=0;i<nonmst.size();++i){
            if(l[i]<r[i]){
                done=false;
                res[(l[i]+r[i]+1)/2].emplace_back(i);
            }
        }
        if(done)break;
        iota(p,p+N,0);
        for(int i=0;i<mst.size();++i){
            for(auto j:res[i]){
                auto [w,u,v]=nonmst[j];
                u=fp(u),v=fp(v);
                if(u==v)r[j]=i-1;
                else l[j]=i;
            }
            auto [w,u,v]=mst[i];
            u=fp(u),v=fp(v);
            p[u]=v;
        }
    }
    int ans=2e9;
    for(int i=0;i<nonmst.size();++i){
        ans=min(ans,get<0>(nonmst[i])-get<0>(mst[l[i]]));
    }
    cout << ans;
}
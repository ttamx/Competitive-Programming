#include <bits/stdc++.h>
#include "sphinx.h"

using namespace std;

vector<int> find_colours(int n,vector<int> X,vector<int> Y){
    int m=X.size();
    vector<int> ans(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        adj[X[i]].emplace_back(Y[i]);
        adj[Y[i]].emplace_back(X[i]);
    }
    auto count_n=[&](vector<int> col){
        vector<int> pa(n);
        iota(pa.begin(),pa.end(),0);
        function<int(int)> fp=[&](int u){
            return pa[u]=(u==pa[u]?u:fp(pa[u]));
        };
        auto uni=[&](int u,int v){
            u=fp(u),v=fp(v);
            if(u!=v){
                pa[v]=u;
            }
        };
        for(int i=0;i<m;i++){
            if(col[X[i]]==n&&col[Y[i]]==n){
                uni(X[i],Y[i]);
            }
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(col[i]==n&&fp(i)==i){
                res++;
            }
        }
        return res;
    };
    auto query=[&](vector<int> a){
        return perform_experiment(a)-count_n(a);
    };
    vector<bool> vis(n);
    int comp_cnt=0;
    vector<int> pa(n);
    iota(pa.begin(),pa.end(),0);
    function<int(int)> fp=[&](int u){
        return pa[u]=(u==pa[u]?u:fp(pa[u]));
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u!=v){
            pa[v]=u;
            comp_cnt--;
        }
    };
    int node_cnt=0;
    vector<int> filter(n,n);
    function<void(int)> dfs=[&](int u){
        node_cnt++,comp_cnt++;
        filter[u]=-1;
        int res=query(filter);
        int k=comp_cnt-res;
        vector<int> same;
        for(int i=0,p=0;i<k;i++){
            int l=p,r=n-1;
            while(l<r){
                int m=(l+r)/2;
                vector<int> tmp(n,n);
                int cnt=0;
                for(int j=0;j<n;j++){
                    if(vis[j]){
                        if(p<=fp(j)&&fp(j)<=m){
                            if(fp(j)==j){
                                cnt++;
                            }
                        }else{
                            tmp[j]=-1;
                        }
                    }
                }
                tmp[u]=-1;
                if(query(tmp)!=res-cnt){
                    r=m;
                }else{
                    l=m+1;
                }
            }
            vector<int> tmp(n,n);
            int cnt=0;
            for(int j=0;j<n;j++){
                if(vis[j]&&(fp(j)>l||fp(j)<p)){
                    tmp[j]=-1;
                    if(fp(j)==j){
                        cnt++;
                    }
                }
            }
            tmp[u]=-1;
            same.emplace_back(l);
            p=l+1;
        }
        vis[u]=true;
        for(auto x:same){
            uni(u,x);
        }
        for(auto v:adj[u]){
            if(!vis[v]){
                dfs(v);
            }
        }
    };
    dfs(0);
    set<pair<int,int>> edge;
    for(int i=0;i<m;i++){
        int u=fp(X[i]),v=fp(Y[i]);
        if(u>v){
            swap(u,v);
        }
        edge.emplace(u,v);
    }
    vector<vector<int>> adj2(n);
    for(auto [u,v]:edge){
        adj2[u].emplace_back(v);
        adj2[v].emplace_back(u);
    }
    int root=fp(0);
    for(int i=0;i<n;i++){
        ans[i]=fp(i);
    }
    return ans;
}

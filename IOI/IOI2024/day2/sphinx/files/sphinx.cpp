#include <bits/stdc++.h>
#include "sphinx.h"

using namespace std;

vector<int> find_colours(int n,vector<int> X,vector<int> Y){
    int m=X.size();
    vector<int> ans(n,-1);
    auto count_col=[&](vector<int> a,int col){
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
            if(a[X[i]]==col&&a[Y[i]]==col){
                uni(X[i],Y[i]);
            }
        }
        int res=0;
        for(int i=0;i<n;i++){
            if(a[i]==col&&fp(i)==i){
                res++;
            }
        }
        return res;
    };
    auto query=[&](vector<int> a,int col){
        int res=perform_experiment(a)-count_col(a,col);
        if(col!=n){
            res-=count_col(a,n);
        }
        return res;
    };
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
    vector<int> filter(n,n);
    for(int u=0;u<n;u++){
        comp_cnt++;
        filter[u]=-1;
        int res=query(filter,n);
        int k=comp_cnt-res;
        vector<int> same,cand;
        for(int i=0;i<u;i++){
            if(fp(i)==i){
                cand.emplace_back(i);
            }
        }
        for(int i=0,p=0;i<k;i++){
            int l=p,r=cand.size()-1;
            while(l<r){
                int m=(l+r)/2;
                vector<int> tmp(n,n);
                int cnt=0;
                for(int j=0;j<u;j++){
                    if(cand[p]<=fp(j)&&fp(j)<=cand[m]){
                        if(fp(j)==j){
                            cnt++;
                        }
                    }else{
                        tmp[j]=-1;
                    }
                }
                tmp[u]=-1;
                if(query(tmp,n)!=res-cnt){
                    r=m;
                }else{
                    l=m+1;
                }
            }
            same.emplace_back(cand[l]);
            p=l+1;
        }
        for(auto x:same){
            uni(u,x);
        }
    }
    set<pair<int,int>> edge;
    for(int i=0;i<m;i++){
        int u=fp(X[i]),v=fp(Y[i]);
        if(u>v){
            swap(u,v);
        }
        if(u!=v){
            edge.emplace(u,v);
        }
    }
    vector<vector<int>> adj(n);
    for(auto [u,v]:edge){
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<vector<int>> comp(n);
    for(int i=0;i<n;i++){
        comp[fp(i)].emplace_back(i);
    }
    vector<bool> vis(n);
    vector<vector<int>> node(2);
    int node_cnt=0;
    function<void(int,int)> dfs=[&](int u,int c){
        node_cnt++;
        vis[u]=true;
        node[c].emplace_back(u);
        for(auto v:adj[u]){
            if(!vis[v]){
                dfs(v,c^1);
            }
        }
    };
    for(auto &x:node){
        sort(x.begin(),x.end());
    }
    dfs(fp(0),0);
    auto paint=[&](vector<int> &a,int i,int col){
        for(auto x:comp[i]){
            a[x]=col;
        }
    };
    if(node_cnt==1){
        for(int i=0;i<n;i++){
            vector<int> tmp(n,i);
            tmp[0]=-1;
            if(perform_experiment(tmp)==1){
                return vector<int>(n,i);
            }
        }
        assert(false);
    }
    vector<vector<int>> pos(2);
    for(int i=0;i<2;i++){
        int k=node[i].size();
        pos[i].resize(k);
        iota(pos[i].begin(),pos[i].end(),0);
    }
    for(int col=0;col<n;col++){
        for(int t=0;t<2;t++){
            vector<int> filter(n,col);
            for(auto i:node[t]){
                paint(filter,i,-1);
            }
            vector<int> found;
            for(int i=0;i<pos[t].size();i++){
                for(int j=0;j<pos[t][i];j++){
                    paint(filter,node[t][j],n);
                }
                if(query(filter,col)==node[t].size()-pos[t][i]){
                    break;
                }
                int l=i,r=pos[t].size()-1;
                while(l<r){
                    int m=(l+r)/2;
                    vector<int> tmp(n,col);
                    for(int j=0;j<node[t].size();j++){
                        if(j<pos[t][i]||pos[t][m]<j){
                            paint(tmp,node[t][j],n);
                        }else{
                            paint(tmp,node[t][j],-1);
                        }
                    }
                    if(query(tmp,col)!=pos[t][m]-pos[t][i]+1){
                        r=m;
                    }else{
                        l=m+1;
                    }
                }
                ans[node[t][pos[t][l]]]=col;
                found.emplace_back(pos[t][l]);
                i=l;
            }
            for(auto i:found){
                pos[t].erase(lower_bound(pos[t].begin(),pos[t].end(),i));
            }
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=ans[fp(i)];
        assert(ans[i]!=-1);
    }
    return ans;
}

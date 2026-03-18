#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m;
    char c;
    cin >> m >> c;
    int n=1;
    vector<int> a{-1};
    vector<int> p{0};
    vector<vector<int>> adj(1);
    for(int i=0;i<m;i++){
        vector<int> np;
        for(auto &pp:p){
            string x;
            cin >> x;
            adj.push_back(vector<int>());
            adj[pp].emplace_back(n);
            a.emplace_back(-1);
            if(x=="T"){
                a[n]=1;
            }else if(x=="F"){
                a[n]=0;
            }else{
                int v=stoi(x);
                while(v--){
                    np.emplace_back(n);
                }
            }
            n++;
        }
        p=move(np);
    }
    function<array<int,2>(int,int)> dfs=[&](int u,int op){
        array<int,2> res;
        int sum=0,opt=0,mn=INF;
        for(auto v:adj[u]){
            auto d=dfs(v,op^1);
            sum+=d[op];
            opt+=min(d[0],d[1]);
            mn=min(mn,d[op^1]-min(d[0],d[1]));
        }
        if(a[u]==-1){
            res[op]=sum;
            res[op^1]=opt+mn;
        }else{
            res[a[u]]=0;
            res[a[u]^1]=1;
        }
        return res;
    };
    auto ans=dfs(1,c=='A');
    cout << max(ans[0],ans[1]) << "\n";
}
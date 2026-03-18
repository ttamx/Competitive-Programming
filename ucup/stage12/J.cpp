#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int W=8;


int n,m,k;
vector<int> adj[N][W];
vector<int> ans;

inline void compress(vector<pair<int,ll>> &a){
    vector<pair<int,ll>> b;
    sort(a.begin(),a.end());
    for(auto [x,c]:a){
        if(!b.empty()&&b.back().first==x)b.back().second+=c;
        else b.emplace_back(x,c);
    }
    a=move(b);
}

void rec(const vector<pair<int,ll>> &a,int len){
    if(a.empty())return;
    for(auto [u,c]:a){
        for(int i=0;i<c;i++){
            ans.emplace_back(len);
            if(ans.size()==k){
                for(auto e:ans){
                    cout << e << "\n";
                }
                exit(0);
            }
        }
    }
    for(int i=0;i<8;i++){
        vector<pair<int,ll>> b;
        for(auto [u,c]:a){
            for(auto v:adj[u][i]){
                b.emplace_back(v,c);
            }
        }
        compress(b);
        rec(b,len+1);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    vector<pair<int,ll>> a[W];
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u][w-1].emplace_back(v);
        a[w-1].emplace_back(v,1);
    }
    for(int i=0;i<W;i++){
        compress(a[i]);
        rec(a[i],1);
    }
    ans.resize(k,-1);
    for(auto x:ans){
        cout << x << "\n";
    }
}
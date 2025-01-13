#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n;
string s;
vector<pair<int,int>> adj[N];
int ans=0;
bool b[N],w[N],lb[N],lw[N];
pair<int,int> e[N];

bool dfsb(int u,int p,bool st=true){
    int cnt=0;
    for(auto [v,i]:adj[u]){
        if(v==p)continue;
        if(dfsb(v,u,false)){
            b[i]=true;
            cnt++;
            ans++;
        }
    }
    if(s[u]=='B'&&(cnt==0||(st&&cnt==1))){
        lb[u]=true;
    }
    return s[u]=='B'||(cnt>0);
}

bool dfsw(int u,int p,bool st=true){
    int cnt=0;
    for(auto [v,i]:adj[u]){
        if(v==p)continue;
        if(dfsw(v,u,false)){
            w[i]=true;
            cnt++;
            ans++;
        }
    }
    if(s[u]=='W'&&(cnt==0||(st&&cnt==1))){
        lw[u]=true;
    }
    return s[u]=='W'||(cnt>0);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    for(int i=0;i<n-1;i++){
        auto &[u,v]=e[i];
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    for(int i=0;i<n;i++){
        if(s[i]=='B'){
            dfsb(i,-1);
            break;
        }
    }
    for(int i=0;i<n;i++){
        if(s[i]=='W'){
            dfsw(i,-1);
            break;
        }
    }
    int cnt=0;
    for(int i=0;i<n-1;i++){
        auto [u,v]=e[i];
        if(b[i]&&w[i]){
            for(int t=0;t<2;t++){
                if(lb[u]&&lw[v]){
                    cnt++;
                }
                swap(u,v);
            }
        }
    }
    assert(cnt<=1);
    cout << ans-cnt;
}
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<char> op(n+k-1);
    vector<vector<pair<int,int>>> adj(n);
    vector<tuple<int,int,int>> qq;
    vector<vector<int>> qr(n);
    for(int i=0;i<n+k-1;i++){
        cin >> op[i];
        if(op[i]=='S'){
            int u,v;
            cin >> u >> v;
            u--,v--;
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
        }else if(op[i]=='Q'){
            int a,d;
            cin >> a >> d;
            a--,d--;
            qq.emplace_back(a,d,i);
        }else if(op[i]=='C'){
            int d;
            cin >> d;
            d--;
            qr[d].emplace_back(i);
        }
    }
    vector<int> dp(n);
    
}
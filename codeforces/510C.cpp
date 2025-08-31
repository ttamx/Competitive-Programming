#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> deg(26);
    vector<vector<int>> adj(26);
    auto link=[&](char u,char v){
        u-='a',v-='a';
        adj[u].emplace_back(v);
        deg[v]++;
    };
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int k=0;
            while(k<a[i].size()&&k<a[j].size()&&a[i][k]==a[j][k])k++;
            if(k==a[j].size()){
                cout << "Impossible\n";
                exit(0);
            }
            if(k==a[i].size())continue;
            link(a[i][k],a[j][k]);
        }
    }
    vector<int> q;
    for(int i=0;i<26;i++){
        if(deg[i]==0){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<q.size();i++){
        int u=q[i];
        for(auto v:adj[u]){
            if(--deg[v]==0){
                q.emplace_back(v);
            }
        }
    }
    if(q.size()<26){
        cout << "Impossible\n";
    }else{
        for(auto x:q)cout << char('a'+x);
        cout << "\n";
    }
}
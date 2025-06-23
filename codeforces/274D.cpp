#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj((n+1)*m);
    vector<int> deg((n+1)*m);
    int cur=m;
    for(int i=0;i<n;i++){
        vector<pair<int,int>> a;
        for(int j=0;j<m;j++){
            int x;
            cin >> x;
            if(x!=-1){
                a.emplace_back(x,j);
            }
        }
        sort(a.begin(),a.end());
        int last=-1,last2=-1,val=-1;
        vector<int> b;
        for(auto [x,j]:a){
            if(x!=val){
                last=last2;
                last2=cur;
                val=x;
                for(auto k:b){
                    adj[k].emplace_back(last);
                    deg[last]++;
                }
                b.clear();
                cur++;
            }
            if(last!=-1){
                adj[last].emplace_back(j);
                deg[j]++;
            }
            b.emplace_back(j);
        }
    }
    vector<int> q;
    for(int i=0;i<(n+1)*m;i++){
        if(deg[i]==0){
            q.emplace_back(i);
        }
    }
    vector<int> ans;
    for(int i=0;i<q.size();i++){
        int u=q[i];
        if(u<m)ans.emplace_back(u);
        for(auto v:adj[u]){
            if(--deg[v]==0){
                q.emplace_back(v);
            }
        }
    }
    if(ans.size()<m){
        cout << -1 << "\n";
    }else{
        for(auto x:ans){
            cout << x+1 << " ";
        }
        cout << "\n";
    }
}
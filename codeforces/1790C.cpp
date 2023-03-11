#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> d(n);
    for(int i=0;i<n;i++){
        int u=-1,v;
        for(int j=1;j<n;j++){
            cin >> v;
            v--;
            if(u>-1){
                adj[u].push_back(v);
                d[v]++;
            }
            u=v;
        }
    }
    queue<int> q;
    int r=0;
    for(int i=0;i<n;i++)if(d[i]==0)r=i;
    q.push(r);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout << u+1 << ' ';
        for(auto v:adj[u])if(--d[v]==0)q.push(v);
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
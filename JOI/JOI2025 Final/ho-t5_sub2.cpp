#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int M=2e5+5;

int n,m;
int p[N];
int a[M],b[M];
priority_queue<int> pq[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i];
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        cin >> a[i] >> b[i];
        int u=a[i];
        int dist=0;
        while(u!=b[i]){
            if(++dist>=n){
                cout << -1 << "\n";
                exit(0);
            }
            u=p[u];
        }
        pq[a[i]].emplace(dist);
    }
    for(int t=0;;t++){
        bool done=true;
        vector<pair<int,int>> todo;
        for(int i=1;i<=n;i++){
            if(!pq[i].empty()){
                done=false;
                int cur=pq[i].top();
                pq[i].pop();
                if(cur>1){
                    todo.emplace_back(p[i],cur-1);
                }
            }
        }
        if(done){
            cout << t << "\n";
            exit(0);
        }
        for(auto [i,v]:todo){
            pq[i].emplace(v);
        }
    }
}
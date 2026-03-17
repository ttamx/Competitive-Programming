#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,x,y;
    cin >> n >> x >> y;
    vector<int> d(1<<n,-1);
    queue<int> q;
    d[1<<(n-1)]=0;
    q.emplace(1<<(n-1));
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u%2==0){
            for(auto v:{u/2,(u+(1<<n))/2}){
                if(d[v]==-1){
                    d[v]=d[u]+1;
                    q.emplace(v);
                }
            }
        }
    }
    cout << max(d[x],d[y]) << "\n";
}
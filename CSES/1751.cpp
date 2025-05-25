#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N];
int mark[N];
bool vis[N];
int dp[N];

int calc(int u){
    if(vis[u]){
        return dp[u];
    }
    vis[u]=true;
    return dp[u]=calc(a[u])+1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        if(mark[i])continue;
        int j=i;
        while(!mark[j]){
            mark[j]=i;
            j=a[j];
        }
        if(mark[j]==i){
            vector<int> cycle;
            int k=j;
            do{
                cycle.emplace_back(k);
                k=a[k];
            }while(k!=j);
            for(auto u:cycle){
                vis[u]=true;
                dp[u]=cycle.size();
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout << calc(i) << " \n"[i==n];
    }
}
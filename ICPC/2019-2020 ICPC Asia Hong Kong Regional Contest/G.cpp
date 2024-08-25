#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k;
    cin >> k;
    int n=0;
    vector<int> par,cost;
    auto new_node=[&](int p){
        par.emplace_back(p);
        cost.emplace_back(0);
        return n++;
    };
    int p=-1;
    function<int(int,int)> solve=[&](int k,int p){
        int u=new_node(p);
        if(k==1){
            cost[new_node(u)]=2;
            return cost[u]=1;
        }
        int x=new_node(u);
        cost[x]=1;
        int y=new_node(x);
        cost[y]=1;
        int res=1+solve(k>>1,u);
        cost[u]=res+(k%2==0);
        return res;
    };
    solve(k,-1);
    cout << n << "\n";
    for(int i=1;i<n;i++)cout << par[i]+1 << " \n"[i==n-1];
    for(int i=0;i<n;i++)cout << cost[i] << " \n"[i==n-1];
}
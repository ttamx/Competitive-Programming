#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m);
    for(auto &[u,v]:a)cin >> u >> v;
    cout << "YES\n";
    cout << m*4 << "\n";
    for(auto [u,v]:a){
        cout << u << " " << v << " ";
        for(int i=1;i<=n;i++)if(i!=u&&i!=v)cout << i << " ";
        cout << "\n";
        for(int i=1;i<=n;i++)if(i!=u&&i!=v)cout << i << " ";
        cout << u << " " << v << " ";
        cout << "\n";
        cout << u << " " << v << " ";
        for(int i=n;i>=1;i--)if(i!=u&&i!=v)cout << i << " ";
        cout << "\n";
        for(int i=n;i>=1;i--)if(i!=u&&i!=v)cout << i << " ";
        cout << u << " " << v << " ";
        cout << "\n";
    }
}
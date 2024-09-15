#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k;
    cin >> k;
    vector<pair<int,int>> edges;
    vector<array<int,2>> id(k+2);
    int n=0;
    for(int i=0;i<k+2;i++){
        id[i][0]=n++;
        id[i][1]=n++;
        for(int j=0;j<i;j++){
            edges.emplace_back(id[i][0],id[j][1]);
            edges.emplace_back(id[i][1],id[j][0]);
        }
    }
    edges.emplace_back(id[k+1][0],id[k+1][1]);
    cout << n << " " << edges.size() << " " << 2 << "\n";
    for(int i=0;i<n;i++){
        cout << i%2+1 << " \n"[i==n-1];
    }
    for(auto [u,v]:edges){
        cout << u+1 << " " << v+1 << "\n";
    }
}
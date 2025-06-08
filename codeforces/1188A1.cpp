#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        deg[u]++,deg[v]++;
    }
    cout << (count(deg.begin(),deg.end(),2)?"NO":"YES") << "\n";
}
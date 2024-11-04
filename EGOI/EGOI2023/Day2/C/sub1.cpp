#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    int root=0;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
    }
    for(int i=0;i<k;i++){
        int u,v;
        cin >> u >> v;
        root=u;
    }
    for(int i=0;i<n;i++){
        if(i!=root){
            cout << i << " " << root << "\n";
        }
    }
}
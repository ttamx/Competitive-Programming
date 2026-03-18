#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return u==fa[u]?u:fa[u]=fp(fa[u]);
    };
    vector<pair<int,int>> bad;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(fp(u)==fp(v)){
            bad.emplace_back(u,v);
        }else{
            fa[fp(u)]=fp(v);
        }
    }
    vector<int> s;
    for(int i=0;i<n;i++)if(i==fp(i))s.emplace_back(i);
    cout << bad.size() << "\n";
    for(auto [u,v]:bad){
        cout << u+1 << " " << v+1 << " " << s[0]+1 << " " << s.back()+1 << "\n";
        s.pop_back();
    }
}
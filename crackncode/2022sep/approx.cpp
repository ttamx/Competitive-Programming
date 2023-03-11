#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,r,q;
int p[N];

int fp(int u){
    if(u==p[u])return p[u];
    return p[u]=fp(p[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> r >> q;
    iota(p,p+n+1,0);
    for(int i=0;i<r;++i){
        int u,v;
        cin >> u >> v;
        p[fp(u)]=fp(v);
    }
    for(int i=0;i<q;++i){
        int u,v;
        cin >> u >> v;
        cout << ((fp(u)==fp(v))? "Y":"N") << "\n";
    }
}

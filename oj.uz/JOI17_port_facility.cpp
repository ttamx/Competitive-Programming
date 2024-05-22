#include<bits/stdc++.h>

using namespace std;

const int N=2e6+5;
const int MOD=1e9+7;

int n;
int a[N],p[2*N];
int ans=1;
set<int> s;

int fp(int u){
    return p[u]=u==p[u]?u:fp(p[u]);
}

void uni(int u,int v){
    p[fp(u)]=fp(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x >> a[x];
    }
    iota(p,p+4*n+1,0);
    for(int i=1;i<=2*n;i++)if(a[i]){
        auto l=s.lower_bound(i),r=s.lower_bound(a[i]);
        for(auto it=l;it!=r;it++){
            uni(a[i],*it+2*n);
            uni(a[i]+2*n,*it);
            if(fp(*it)==fp(*prev(r)))break;
        }
        s.emplace(a[i]);
    }
    for(int i=1;i<=2*n;i++)if(a[i]){
        if(fp(a[i])==fp(a[i]+2*n))cout << 0,exit(0);
        if(fp(a[i])==a[i]){
            ans*=2;
            if(ans>=MOD)ans-=MOD;
        }
    }
    cout << ans;
}
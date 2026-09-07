#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,k;
    cin >> n >> q >> k;
    vector<ll> h(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p >> h[i];
        h[i]+=h[p-1];
    }
    auto a=h;
    sort(a.begin(),a.end());
    vector<int> id(n),nxt(n),jump(n),dep(n);
    for(int i=0;i<n;i++)id[i]=lower_bound(a.begin(),a.end(),h[i])-a.begin();
    for(int i=0,j=0;i<n;i++){
        while(j+1<n&&a[j+1]-a[i]<=k)j++;
        nxt[i]=j;
    }
    for(int i=n-1;i>=0;i--){
        if(nxt[i]==i){
            jump[i]=i;
            continue;
        }
        int p=nxt[i];
        dep[i]=dep[p]+1;
        jump[i]=(dep[p]-dep[jump[p]]==dep[jump[p]]-dep[jump[jump[p]]]?jump[jump[p]]:p);
    }
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        u=id[u],v=id[v];
        if(u>v)swap(u,v);
        int s=u;
        while(nxt[u]!=u){
            if(a[jump[u]]<a[v])u=jump[u];
            else if(a[nxt[u]]<a[v])u=nxt[u];
            else break;
        }
        u=nxt[u];
        cout << (a[u]>=a[v]?max(1,dep[s]-dep[u]):-1) << "\n";
    }
}
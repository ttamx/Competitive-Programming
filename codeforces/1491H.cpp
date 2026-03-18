#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=320;

int n,q,k;
int par[N],jump[N];
int lz[K];
bool done[K];

void recalc(int id,int x){
    if(done[id]){
        lz[id]=min(lz[id]+x,n);
        return;
    }
    done[id]=true;
    for(int i=id*k;i<n&&i<(id+1)*k;i++){
        par[i]=max((i==0?-1:0),par[i]-x);
        if(par[i]<id*k){
            jump[i]=i;
        }else{
            jump[i]=jump[par[i]];
            done[id]=false;
        }
    }
}

inline int getpar(int u){
    return max(0,par[u]-lz[u/k]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    par[0]=-1;
    for(int i=1;i<n;i++){
        cin >> par[i];
        par[i]--;
        jump[i]=i;
    }
    while(k*k<n){
        k++;
    }
    for(int i=0;i<k;i++){
        recalc(i,0);
    }
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int l,r,x;
            cin >> l >> r >> x;
            l--,r--;
            int bl=l/k,br=r/k;
            if(l/k==r/k){
                for(int i=l;i<=r;i++){
                    par[i]=max(0,par[i]-x);
                }
                recalc(bl,0);
            }else{
                for(int i=l;i<(bl+1)*k;i++){
                    par[i]=max(0,par[i]-x);
                }
                for(int i=br*k;i<=r;i++){
                    par[i]=max(0,par[i]-x);
                }
                recalc(bl,0);
                recalc(br,0);
                for(int i=bl+1;i<br;i++){
                    recalc(i,x);
                }
            }
        }else{
            int u,v;
            cin >> u >> v;
            u--,v--;
            while(jump[u]!=jump[v]){
                if(u<v)swap(u,v);
                u=getpar(jump[u]);
            }
            while(u!=v){
                if(u<v)swap(u,v);
                u=getpar(u);
            }
            cout << u+1 << "\n";
        }
    }
}
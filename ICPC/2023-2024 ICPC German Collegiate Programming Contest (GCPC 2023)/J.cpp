#include<bits/stdc++.h>

using namespace std;

const int H=2e5+5;
const int K=1<<19;
const int W=20;

int w,h,q;

struct Info:array<int,W>{
    Info(){
        iota(this->begin(),this->end(),0);
    }
    friend Info operator+(const Info &l,const Info &r){
        Info res;
        for(int i=0;i<W;i++){
            res[i]=r[l[i]];
        }
        return res;
    }
};

struct Segtree{
    Info t[K];
    void modify(int l,int r,int i,int x,int u,int v){
        if(l==r){
            swap(t[i][u],t[i][v]);
            return;
        }
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,u,v);
        else modify(m+1,r,i*2+1,x,u,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,int u,int v){
        modify(1,h,1,x,u,v);
    }
    int query(){
        Info p=t[1];
        array<bool,W> vis{};
        int res=0;
        for(int i=0;i<w;i++){
            if(vis[i])continue;
            res++;
            for(int j=i;!vis[j];j=p[j]){
                vis[j]=true;
            }
        }
        return res;
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> w >> h >> q;
    while(q--){
        int x,u,v;
        cin >> x >> u >> v;
        u--,v--;
        seg.modify(x,u,v);
        cout << w-seg.query() << "\n";
    }
}
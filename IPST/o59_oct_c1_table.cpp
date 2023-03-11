#include<bits/stdc++.h>

using namespace std;

const int N=(1<<14)+5;

int R,C,M;

struct segtree{
    int tree[N],lz[N];

    void pushlz(int l,int r,int i){
        if(lz[i]==0)return;
        tree[i]=lz[i];
        if(l<r)lz[i*2]=lz[(i*2)+1]=lz[i];
        lz[i]=0;
    }

    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(l>y || r<x)return;
        if(x<=l && r<=y){
            lz[i]=v;
            pushlz(l,r,i);
            return;
        }
        if(l==r){tree[i]=v;return;}
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,(i*2)+1,x,y,v);
        tree[i]=min(tree[i*2],tree[(i*2)+1]);
    }

    int query(int l,int r,int i,int ql,int qr){
        pushlz(l,r,i);
        if(qr<l || r<ql)return 2e9;
        if(ql<=l && r<=qr)return tree[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,ql,qr),query(m+1,r,i*2+1,ql,qr));
    }

}seg[305],mn;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> R >> C >> M;
    while(M--){
        int k,r,c,x;
        cin >> k;
        if(k==1){
            cin >> r >> c >> x;
            seg[r].update(1,C,1,c,c,x);
            mn.update(1,R,1,r,r,seg[r].tree[1]);
        }else if(k==2){
            cin >> r >> x;
            seg[r].update(1,C,1,1,C,x);
            mn.update(1,R,1,r,r,seg[r].tree[1]);
        }else if(k==3){
            cin >> r >> c;
            cout << seg[r].query(1,C,1,c,c) << '\n';
        }else if(k==4){
            cout << mn.tree[1] << '\n';
        }
    }
}

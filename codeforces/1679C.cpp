#include<bits/stdc++.h>

using namespace std;

const int K=1<<18;

int n,q;

struct segtree{
    int t[K];
    void update(int l,int r,int i,int &x,int &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return 2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}sx,sy;

void runcase(){
    cin >> n >> q;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            sx.update(x,1);
            sy.update(y,1);
        }else if(t==2){
            int x,y;
            cin >> x >> y;
            sx.update(x,-1);
            sy.update(y,-1);
        }else{
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(sx.query(x1,x2)>0||sy.query(y1,y2)>0)cout << "Yes\n";
            else cout << "No\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
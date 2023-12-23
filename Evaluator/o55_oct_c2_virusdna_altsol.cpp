#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e6+5;
const int K=1<<21;

int n,q;
bool del[N];

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=1);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        t[i]+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,v);
        else update(m+1,r,i*2+1,x,v);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    p2 query(int l,int r,int i,int v){
        if(l==r)return p2(l,v);
        int m=(l+r)/2;
        if(t[i*2]>=v)return query(l,m,i*2,v);
        else return query(m+1,r,i*2+1,v-t[i*2]);
    }
    p2 query(int v){
        return query(1,n,1,v);
    }
}s;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<=n)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f1,f2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    s.build();
    while(q--){
        char o;
        cin >> o;
        if(o=='d'){
            int x;
            cin >> x;
            x++;
            auto [id,val]=s.query(x);
            s.update(id,-1);
            if(val==1&&!del[id]){
                del[id]=true;
                f1.add(id,1);
            }else{
                f2.add(id,-1);
            }
        }else if(o=='g'){
            int x;
            cin >> x;
            x++;
            auto [id,val]=s.query(x);
            s.update(id,1);
            f2.add(id,1);
        }else{
            int x,y;
            cin >> x >> y;
            cout << f1.read(y-1)-f1.read(x-1)+f2.read(y-1)-f2.read(x-1) << "\n";
        }
    }
}
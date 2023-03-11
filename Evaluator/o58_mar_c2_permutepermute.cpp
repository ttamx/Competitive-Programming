#include<bits/stdc++.h>

using namespace std;

const int N=1<<19;
const int M=1e5+5;

struct node{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    
    void print(){
        for(auto i:a)cout << i << ' ';
    }

    friend node operator+(node &lhs,node &rhs){
        node ret;
        for(int i=0;i<10;++i)ret.a[i]=rhs.a[lhs.a[i]];
        return ret;
    }
}I;

struct segtree{
    node tree[N];

    void update(int l,int r,int i,int x,node v){
        if(l>x||r<x)return;
        if(l==r){
            tree[i]=v;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,i*2,x,v);
        update(mid+1,r,i*2+1,x,v);
        tree[i]=tree[i*2]+tree[i*2+1];
    }
}s;

int n,m;
int pre[M];
vector<int> pos;
pair<int,node> d[M];
vector<pair<int,int>> in;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;++i){
        auto &[x,y]=d[i];
        cin >> x;
        for(int j=0;j<10;++j)cin >> y.a[j];
        pos.emplace_back(x);
    }
    in.resize(m);
    for(auto &[x,y]:in){
        cin >> x >> y;
        pos.emplace_back(y);
    }
    sort(pos.begin(),pos.end());
    pos.resize(unique(pos.begin(),pos.end())-pos.begin());
    int sz=pos.size();
    for(int i=1;i<=n;++i){
        auto &[x,y]=d[i];
        x=lower_bound(pos.begin(),pos.end(),x)-pos.begin()+1;
        s.update(1,sz,1,x,y);
        pre[i]=x;
    }
    for(auto &[x,y]:in){
        y=lower_bound(pos.begin(),pos.end(),y)-pos.begin()+1;
        s.update(1,sz,1,pre[x],I);
        s.update(1,sz,1,y,d[x].second);
        pre[x]=y;
        cout << s.tree[1].a[0] << '\n';
    }
}
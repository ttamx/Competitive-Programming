#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=200005;

int n,k;
int a[N],l[N],r[N];
stack<int> s;
int root;
vector<int> upd[N];
int del[N];
stack<int> ver;

void dfs(int u,int lo,int hi){
    if(!u)return;
    upd[lo].emplace_back(a[u]);
    del[hi+k]++;
    dfs(l[u],lo,u-1);
    dfs(r[u],u+1,hi);
}

struct Line{
    ll m,c;
    ll eval(ll x){return m*x+c;}
};

struct LiChao{
    struct Node{
        int l,r;
        Line v;
        ll mx;
        Node():l(-1),r(-1),v{0,0},mx(0){}
    };
    vector<Node> nodes;
    int new_node(int i){
        nodes.emplace_back(i==-1?Node():nodes[i]);
        return nodes.size()-1;
    }
    int build(int l,int r){
        int i=new_node(-1);
        if(l<r){
            int m=(l+r)/2;
            nodes[i].l=build(l,m);
            nodes[i].r=build(m+1,r);
        }
        return i;
    }
    int build(){return build(1,n);}
    int update(int l,int r,int j,Line v){
        int i=new_node(j);
        int m=(l+r)/2;
        if(v.eval(m)>nodes[i].v.eval(m))swap(v,nodes[i].v);
        if(v.eval(l)>nodes[i].v.eval(l))nodes[i].l=update(l,m,nodes[j].l,v);
        if(v.eval(r)>nodes[i].v.eval(r))nodes[i].r=update(m+1,r,nodes[j].r,v);
        nodes[i].mx=max({nodes[i].mx,nodes[i].v.eval(l),nodes[i].v.eval(r)});
        if(l<r)nodes[i].mx=max({nodes[i].mx,nodes[nodes[i].l].mx,nodes[nodes[i].r].mx});
        return i;
    }
    int update(int j,Line v){return update(1,n,j,v);}
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        cerr << "QUERY " << l << " " << r << ", " << x << " " << y << " : " << nodes[i].v.m << ", " << nodes[i].v.c << " " << nodes[i].mx << "\n";
        if(x<=l&&r<=y)return nodes[i].mx;
        int m=(l+r)/2;
        return max({query(l,m,nodes[i].l,x,y),query(m+1,r,nodes[i].r,x,y),nodes[i].v.eval(x),nodes[i].v.eval(y)});
    }
    ll query(int i,int x,int y){return query(1,n,i,x,y);}
}lct;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]>a[i]){
            l[i]=s.top();
            s.pop();
        }
        (s.empty()?root:r[s.top()])=i;
        s.emplace(i);
    }
    dfs(root,1,n);
    ver.emplace(lct.build());
    for(int i=1;i<=n;i++){
        while(del[i]--)ver.pop();
        cerr << i << " : ";
        for(auto v:upd[i]){
            cerr << v << " ";
            ver.emplace(lct.update(ver.top(),Line{v,-1LL*v*(i-1)}));
        }
        cerr << "\n";
        if(i>=k)cout << lct.query(ver.top(),i-k+1,i) << " ";
    }
}
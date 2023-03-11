#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1<<19;

int n,q;
int hsh[N];
vector<int> pos;
vector<tuple<int,int,int,ll>> in;
bool islz[N];
ll tree[N],lz[N];

void pushlz(int l,int r,int i){
    if(islz[i]){
        islz[i]=false;
        tree[i]=lz[i]*(pos[r+1]-pos[l]);
        if(l!=r){
            islz[i*2]=true;
            islz[i*2+1]=true;
            lz[i*2]=lz[i];
            lz[i*2+1]=lz[i];
        }
    }
}

void update(int l,int r,int i,int x,int y,ll v){
    pushlz(l,r,i);
    if(r<x||y<l)return;
    if(x<=l&&r<=y){
        islz[i]=true;
        lz[i]=v;
        pushlz(l,r,i);
        return;
    }
    int m=(l+r)/2;
    update(l,m,i*2,x,y,v);
    update(m+1,r,i*2+1,x,y,v);
    tree[i]=tree[i*2]+tree[i*2+1];
}

ll query(ll l,ll r,ll i,ll x,ll y){
    pushlz(l,r,i);
    if(r<x||y<l)return 0;
    if(x<=l&&r<=y)return tree[i];
    int m=(l+r)/2;
    return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    in.resize(q);
    for(auto &[o,x,y,v]:in){
        cin >> o >> x >> y;
        if(o==0)cin >> v;
        pos.emplace_back(x);
        pos.emplace_back(y);
    }
    pos.emplace_back(0);
    pos.emplace_back(n);
    sort(pos.begin(),pos.end());
    pos.resize(unique(pos.begin(),pos.end())-pos.begin());
    int sz=pos.size();
    for(auto &[o,x,y,v]:in){
        x=lower_bound(pos.begin(),pos.end(),x)-pos.begin();
        y=lower_bound(pos.begin(),pos.end(),y)-pos.begin()-1;
        if(o==0)update(0,sz-1,1,x,y,v);
        else cout << query(0,sz-1,1,x,y) << '\n';
    }
}
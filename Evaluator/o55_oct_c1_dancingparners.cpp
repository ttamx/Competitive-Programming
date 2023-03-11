#include<bits/stdc++.h>

using namespace std;

const int K=1<<19;

struct segtree{
    int tree[K];
    void build(int l,int r,int i){
        if(l==r){
            tree[i]=-2e9;
            return;
        }
        int m=(l+r)>>1;
        build(l,m,i<<1);
        build(m+1,r,i<<1|1);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r){
            tree[i]=v;
            return;
        }
        int m=(l+r)>>1;
        update(l,m,i<<1,x,v);
        update(m+1,r,i<<1|1,x,v);
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return -2e9;
        if(x<=l&&r<=y)return tree[i];
        int m=(l+r)>>1;
        return max(query(l,m,i<<1,x,y),query(m+1,r,i<<1|1,x,y));
    }
}s1,s2;

int n,m;
vector<pair<int,int>> a,b;
vector<int> pos;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;++i){
        int x,y;
        cin >> x >> y;
        pos.emplace_back(x);
        a.emplace_back(x,y);
    }
    for(int i=0;i<n;++i){
        int x,y;
        cin >> x >> y;
        pos.emplace_back(x);
        b.emplace_back(x,y);
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    s1.build(0,pos.size()-1,1);
    s2.build(0,pos.size()-1,1);
    for(auto [x,y]:b){
        int idx=lower_bound(pos.begin(),pos.end(),x)-pos.begin();
        s1.update(0,pos.size()-1,1,idx,y-x);
        s2.update(0,pos.size()-1,1,idx,y+x);
    }
    for(auto [x,y]:a){
        int idx=lower_bound(pos.begin(),pos.end(),x)-pos.begin();
        cout << max(x+y+s1.query(0,pos.size()-1,1,idx,pos.size()-1),y-x+s2.query(0,pos.size()-1,1,0,idx)) << '\n';
    }
}
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct node{
    int v,l,r;
}t[20*N];

int n,m,idx;
int mp[N],rt[N];
vector<pair<int,int>> a;

void build(int l,int r,int &i){
    i=++idx;
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t[i].l);
    build(m+1,r,t[i].r);
}

void update(int l,int r,int &i,int x,int v,int k){
    i=++idx;
    t[i]=t[k];
    t[i].v+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t[i].l,x,v,t[k].l);
    else update(m+1,r,t[i].r,x,v,t[k].r);
}

int query(int l,int r,int kl,int kr,int v){
    if(l==r)return l;
    int m=(l+r)/2;
    int val=t[t[kr].l].v-t[t[kl].l].v;
    if(v<=val)return query(l,m,t[kl].l,t[kr].l,v);
    else return query(m+1,r,t[kl].r,t[kr].r,v-val);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++)mp[a[i].second]=i;
    build(0,n-1,rt[0]);
    for(int i=1;i<=n;i++)update(0,n-1,rt[i],mp[i-1],1,rt[i-1]);
    for(int i=0;i<m;i++){
        int l,r,k;
        cin >> l >> r >> k;
        cout << a[query(0,n-1,rt[l-1],rt[r],k)].first << '\n';
    }
}
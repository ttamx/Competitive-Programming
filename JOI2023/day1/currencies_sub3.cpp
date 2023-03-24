#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

struct node{
    ll val;
    int freq;
    node *l,*r;
    node():val(0),freq(0),l(nullptr),r(nullptr){}
    node(int val,int freq):val(val),freq(freq),l(nullptr),r(nullptr){}
    node(int val,int freq,node *l,node *r):val(val),freq(freq),l(l),r(r){}
};

typedef node* nodeptr;

void build(int l,int r,nodeptr &t){
    t=new node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,ll val){
    t=new node(*k);
    t->val+=val;
    t->freq++;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,k->l,x,val);
    else update(m+1,r,t->r,k->r,x,val);
}

int query(int l,int r,nodeptr tl,nodeptr tr,ll val){
    if(l==r){
        if(tr->val-tl->val<=val)return tr->freq-tl->freq;
        return 0;
    }
    int m=(l+r)/2;
    ll sum=tr->l->val-tl->l->val;
    int freq=tr->l->freq-tl->l->freq;
    if(sum<=val)return freq+query(m+1,r,tl->r,tr->r,val-sum);
    return query(l,m,tl->l,tr->l,val);
}

int n,m,q;
int cost[N];
pair<int,int> edge[N];
nodeptr rt[N];
int mp[N];
vector<pair<int,int>> v;
vector<int> vec[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++)cin >> edge[i].first >> edge[i].second;
    for(int i=1;i<=m;i++){
        int x,y;
        cin >> x >> cost[i];
        vec[x].emplace_back(i);
        v.emplace_back(cost[i],i);
    }
    sort(v.begin(),v.end());
    for(int i=0;i<m;i++)mp[v[i].second]=i+1;
    build(1,m,rt[0]);
    for(int i=1;i<=n;i++){
        rt[i]=rt[i-1];
        for(auto j:vec[i])update(1,m,rt[i],rt[i],mp[j],cost[j]);
    }
    while(q--){
        int u,v,x;
        ll y;
        cin >> u >> v >> x >> y;
        if(u>v)swap(u,v);
        int all=rt[v-1]->freq-rt[u-1]->freq;
        int res=query(1,m,rt[u-1],rt[v-1],y);
        cout << max(-1,x-(all-res)) << '\n';
    }
}
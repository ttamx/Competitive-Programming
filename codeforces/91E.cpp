#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll INF=LLONG_MAX/2;

bool querymode=false;

struct Line{
    ll m,c;
    int i;
    mutable ll p;
    bool operator<(const Line &o)const{
        return querymode?p<o.p:m<o.m;
    }
};

struct LineContainer:multiset<Line>{
    ll floor_div(ll a,ll b){
        return a/b-((a^b)<0&&a%b);
    }
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=INF,false;
        if(x->m==y->m)x->p=x->c>=y->c?INF:-INF;
        else x->p=floor_div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void add_line(Line v){
        auto x=insert(v),y=next(x);
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    pair<ll,int> query(ll x){
        if(empty())return make_pair(-INF,-1);
        querymode=true;
        auto it=lower_bound(Line{0,0,0,x});
        querymode=false;
        return make_pair(it->m*x+it->c,it->i);
    }
}t[K];

int n,q;

void insert(int l,int r,int i,int x,Line v){
    t[i].add_line(v);
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)insert(l,m,i*2,x,v);
    else insert(m+1,r,i*2+1,x,v);
}

pair<ll,int> query(int l,int r,int i,int x,int y,ll v){
    if(y<l||r<x)return make_pair(-INF,-1);
    if(x<=l&&r<=y)return t[i].query(v);
    int m=(l+r)/2;
    return max(query(l,m,i*2,x,y,v),query(m+1,r,i*2+1,x,y,v));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int a,b;
        cin >> a >> b;
        insert(1,n,1,i,Line{b,a,i,0});
    }
    while(q--){
        int l,r,t;
        cin >> l >> r >> t;
        cout << query(1,n,1,l,r,t).second << "\n";
    }
}
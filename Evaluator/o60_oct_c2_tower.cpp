#include<bits/stdc++.h>

using namespace std;

const int N=1<<19;

int n,m;
int lz[N];

struct node{
    int l,r,m,c;
}s[N];

node combine(node a,node b){
    if(a.m>b.m)return a;
    if(a.m<b.m)return b;
    node ret;
    ret.l=a.l;
    ret.r=b.r;
    ret.m=a.m;
    ret.c=a.c+b.c-(a.r==b.l);
    return ret;
}

void pushlz(int l,int r,int i){
    if(!lz[i])return;
    s[i].m+=lz[i];
    if(l<r){
        lz[i*2]+=lz[i];
        lz[i*2+1]+=lz[i];
    }
    lz[i]=0;
}

void build(int l,int r,int i){
    if(l==r){
        s[i]={l,r+1,0,1};
        return;
    }
    int md=(l+r)/2;
    build(l,md,i*2);
    build(md+1,r,i*2+1);
    s[i]=combine(s[i*2],s[i*2+1]);
}

void update(int l,int r,int ul,int ur,int i,int v){
    pushlz(l,r,i);
    if(ur<l || r<ul)return;
    if(ul<=l && r<=ur){
        lz[i]+=v;
        pushlz(l,r,i);
        return;
    }
    int md=(l+r)/2;
    update(l,md,ul,ur,i*2,v);
    update(md+1,r,ul,ur,i*2+1,v);
    s[i]=combine(s[i*2],s[i*2+1]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    build(1,n,1);
    while(m--){
        int a,b,x;
        cin >> a >> b >> x;
        update(1,n,a,b,1,x);
        cout << s[1].m << ' ' << s[1].c << '\n';
    }
}

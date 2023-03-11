#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int m,n;
int a[N],qs[N];
int seg[K];
bool lz[K];
map<int,int> mp;

void pushlz(int l,int r,int i){
    if(!lz[i])return;
    lz[i]=false;
    seg[i]=qs[r]-qs[l-1]-seg[i];
    if(l<r){
        lz[i*2]=!lz[i*2];
        lz[i*2+1]=!lz[i*2+1];
    }
}

void build(int l,int r,int i){
    if(l==r){
        seg[i]=qs[l]-qs[l-1];
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,i*2);
    build(mid+1,r,i*2+1);
    seg[i]=seg[i*2]+seg[i*2+1];
}

void update(int l,int r,int i,int x,int y){
    pushlz(l,r,i);
    if(y<l||x>r)return;
    if(x<=l&&r<=y){
        lz[i]=true;
        pushlz(l,r,i);
        return;
    }
    int mid=(l+r)/2;
    update(l,mid,i*2,x,y);
    update(mid+1,r,i*2+1,x,y);
    seg[i]=seg[i*2]+seg[i*2+1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=1;i<=n;++i){
        cin >> a[i];
        qs[i]=a[i];
        mp[a[i]]=i;
    }
    qs[n+1]=m;
    sort(qs+1,qs+n+1);
    for(int i=1;i<=n;++i){
        mp[qs[i]]=i;
    }
    build(1,n+1,1);
    for(int i=1;i<=n;++i){
        update(1,n+1,1,mp[a[i]]+1,n+1);
        cout << seg[1] << '\n';
    }
}

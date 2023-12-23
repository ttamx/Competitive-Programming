#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<20;

int n,k;
int a[N],b[N],c[2*N],t[N];
int side[N];
vector<int> vec[N];
long long ans;

struct segtree{
    int t[K];
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        t[i]=max(t[i],v);
        if(l==r)return;
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
    }
    void update(int x,int v){
        update(1,2*n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,2*n,1,x,y);
    }
}s;

struct fenwick{
    int t[2*N];
    void add(int i,int v){
        while(i<2*N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
        c[i*2-1]=a[i];
        c[i*2]=b[i];
    }
    sort(c+1,c+2*n+1);
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(c+1,c+2*n+1,a[i])-c;
        b[i]=lower_bound(c+1,c+2*n+1,b[i])-c;
    }
    for(int i=1;i<=k;i++){
        cin >> t[i];
        t[i]=upper_bound(c+1,c+2*n+1,t[i])-c-1;
        s.update(t[i],i);
    }
    for(int i=1;i<=n;i++){
        int pos;
        if(a[i]<b[i]){
            pos=s.query(a[i],b[i]-1);
            side[i]=1;
        }else{
            pos=s.query(b[i],a[i]-1);
            side[i]=0;
        }
        if(pos==0)side[i]=0;
        vec[pos].emplace_back(i);
    }
    for(int i=k;i>=0;i--){
        for(auto j:vec[i])ans+=c[(side[j]+f.read(2*n)-f.read(max(a[j],b[j])-1))%2==0?a[j]:b[j]];
        if(t[i])f.add(t[i],1);
    }
    cout << ans;
}
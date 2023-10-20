#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int K=1<<20;

int n;
int a[N],mp[N];
vector<pair<int,int>> v;

struct segtree{
    int s[K],f[K];
    void update(int l,int r,int i,int x,int v,int w){
        if(x<l||r<x)return;
        if(l==r){
            s[i]+=v;
            f[i]+=w;
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,v,w);
        update(m+1,r,i*2+1,x,v,w);
        s[i]=s[i*2]+s[i*2+1];
        f[i]=f[i*2]+f[i*2+1];
    }
    void update(int x,int v,int w){
        update(1,n,1,x,v,w);
    }
    int query(int l,int r,int i,int v){
        if(l==r)return 1;
        int m=(l+r)/2;
        if(s[i*2]<v)return f[i*2]+query(m+1,r,i*2+1,v-s[i*2]);
        return query(l,m,i*2,v);
    }
    int query(int v){
        return query(1,n,1,v);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int sum=0;
    for(int i=1;i<=n;i++)cin >> a[i],v.emplace_back(a[i],i),sum+=a[i];
    sum=(sum/2)+1;
    sort(v.rbegin(),v.rend());
    for(int i=0;i<n;i++)mp[v[i].second]=i+1;
    for(int i=1;i<=n;i++)s.update(mp[i],a[i],1);
    for(int i=1;i<=n;i++){
        s.update(mp[i],-a[i],-1);
        cout << s.query(sum-a[i]) << '\n';
        s.update(mp[i],a[i],1);
    }
}
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n;
long long a[N],qs[N];
vector<long long> v;
int dp[N];

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=-2e9);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=max(t[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return -2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=a[i]+qs[i-1];
        v.push_back(qs[i]);
    }
    v.push_back(0);
    sort(v.begin(),v.end());
    s.build(0,n,1);
    s.update(0,n,1,lower_bound(v.begin(),v.end(),0)-v.begin(),0);
    for(int i=1;i<=n;i++){
        int idx=lower_bound(v.begin(),v.end(),qs[i])-v.begin();
        dp[i]=max(dp[i-1],s.query(0,n,1,0,idx)+i);
        s.update(0,n,1,idx,dp[i]-i);
    }
    cout << dp[n] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
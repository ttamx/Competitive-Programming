#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,q;
int a[N];
int d[N],v1[N],v2[N],l1[N],l2[N];

struct node{
    int val;
    node *l,*r;
    node():val(0),l(nullptr),r(nullptr){}
    node(int val):val(val),l(nullptr),r(nullptr){}
    node(int val,node *l,node *r):val(val),l(l),r(r){}
};
typedef node* nodeptr;

struct maxtree{
    nodeptr rt[N];
    void build(int l,int r,nodeptr &t){
        t=new node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int ver){
        build(1,n,rt[ver]);
    }
    void update(int l,int r,nodeptr &t,nodeptr k,int x,int val){
        t=new node(*k);
        t->val=max(t->val,val);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,val);
        else update(m+1,r,t->r,k->r,x,val);
    }
    void update(int from,int to,int idx,int val){
        update(1,n,rt[to],rt[from],idx,val);
    }
    int query(int l,int r,nodeptr t,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int ver,int l,int r){
        return query(1,n,rt[ver],l,r);
    }
}mxs;

struct mnstree{
    nodeptr rt[N];
    void build(int l,int r,nodeptr &t){
        t=new node(n);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int ver){
        build(1,n,rt[ver]);
    }
    void update(int l,int r,nodeptr &t,nodeptr k,int x,int val){
        t=new node(*k);
        t->val=min(t->val,val);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,val);
        else update(m+1,r,t->r,k->r,x,val);
    }
    void update(int from,int to,int idx,int val){
        update(1,n,rt[to],rt[from],idx,val);
    }
    int query(int l,int r,nodeptr t,int x,int y){
        if(y<l||r<x)return n;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return min(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int ver,int l,int r){
        return query(1,n,rt[ver],l,r);
    }
}mns;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    a[0]=-2e9;
    a[n+1]=2e9;
    for(int i=1;i<n;i++){
        d[i]=a[i+1]-a[i];
    }
    int sum=0;
    for(int i=n-1;i>0;i--){
        v1[i]=l1[i]=sum-d[i];
        sum+=d[i];
    }
    sort(l1+1,l1+n);
    mxs.build(0);
    for(int i=1;i<n;i++){
        int idx=lower_bound(l1+1,l1+n,v1[i])-l1;
        mxs.update(i-1,i,idx,i);
    }
    sum=0;
    for(int i=1;i<n;i++){
        v2[i]=l2[i]=sum-d[i];
        sum+=d[i];
    }
    sort(l2+1,l2+n);
    mns.build(n);
    for(int i=n-1;i>0;i--){
        int idx=lower_bound(l2+1,l2+n,v2[i])-l2;
        mns.update(i+1,i,idx,i);
    }
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        if(x<=a[1]){
            cout << a[n]-x << '\n';
            continue;
        }
        if(x>=a[n]){
            cout << x-a[1] << '\n';
            continue;
        }
        ll ans=0;
        int l=lower_bound(a+1,a+n+1,x)-a-1;
        int r=upper_bound(a+1,a+n+1,x)-a;
        if(r-l==1){
            if(x-a[l]<=a[r]-x){
                ans+=x-a[l];
                x=l;
                l--;
            }else{
                ans+=a[r]-x;
                x=r;
                r++;
            }
        }else{
            x=(l+r)/2;
        }
        while(1<=l&&r<=n){
            if(a[x]-a[l]<=a[r]-a[x]){
                int idx=lower_bound(l1+1,l1+n,a[n]-a[x])-l1-1;
                int res=mxs.query(l-1,1,idx)+1;
                ans+=a[x]-a[res];
                x=res;
                l=res-1;
            }else{
                int idx=upper_bound(l2+1,l2+n,a[x]-a[1])-l2-1;
                int res=mns.query(r,1,idx);
                ans+=a[res]-a[x];
                x=res;
                r=res+1;
            }
        }
        if(r<=n){
            ans+=a[n]-a[x];
        }
        if(1<=l){
            ans+=a[x]-a[1];
        }
        cout << ans << '\n';
    }
}
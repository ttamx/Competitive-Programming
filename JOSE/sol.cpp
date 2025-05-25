#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<pair<int,int>>add[400005];
vector<pair<int,int>>del[400005];
int inf=1e18+5;
struct segtreemx{
    struct node{
        int h,ans;
        node(int _ans=-inf,int _h=-inf){
            ans=_ans,h=_h;
        }
        friend node operator+(node a,node b){
            return node(max(a.ans,b.ans),max(a.h,b.h));
        }
    };
    node info[800005];
    int lz[800005];
    void push(int st,int en,int i){
        if(lz[i]==inf)return;
        //cerr<<st<<" "<<en<<" "<<i<<"\n";
        info[i].ans=max(info[i].ans,info[i].h-lz[i]);
        if(st!=en)lz[i*2]=min(lz[i*2],lz[i]),lz[i*2+1]=min(lz[i*2+1],lz[i]);
        lz[i]=inf;
    }
    void upd(int st,int en,int i,int pos,int val){
        push(st,en,i);
        if(st>pos||en<pos)return;
        if(st==en)return info[i]=node(-inf,val),void();
        int m=(st+en)/2;
        upd(st,m,i*2,pos,val);
        upd(m+1,en,i*2+1,pos,val);
        info[i]=info[i*2]+info[i*2+1];
    }
    void upd(int st,int en,int i,int l,int r,int val){
        push(st,en,i);
        if(st>r||en<l)return;
        if(st>=l&&en<=r)return lz[i]=val,push(st,en,i);
        int m=(st+en)/2;
        upd(st,m,i*2,l,r,val);
        upd(m+1,en,i*2+1,l,r,val);
        info[i]=info[i*2]+info[i*2+1];
    }
    void undo(int st,int en,int i,int pos){
        push(st,en,i);
        if(st>pos||en<pos)return;
        if(st==en)return info[i].h=-inf,void();
        int m=(st+en)/2;
        undo(st,m,i*2,pos);
        undo(m+1,en,i*2+1,pos);
        info[i]=info[i*2]+info[i*2+1];
    }
    node fans(int st,int en,int i,int l,int r){
        push(st,en,i);
        if(st>r||en<l)return node(-inf,-inf);
        if(st>=l&&en<=r)return info[i];
        int m=(st+en)/2;
        return fans(st,m,i*2,l,r)+fans(m+1,en,i*2+1,l,r);
    }
    void build(int st,int en,int i){
        lz[i]=inf;
        info[i]=node();
        if(st==en)return;
        int m=(st+en)/2;
        build(st,m,i*2);
        build(m+1,en,i*2+1);
        info[i]=info[i*2]+info[i*2+1];
    }
}mx;
struct segtreemn{
    struct node{
        int h,ans;
        node(int _ans=-inf,int _h=inf){
            ans=_ans,h=_h;
        }
        friend node operator+(node a,node b){
            return node(max(a.ans,b.ans),min(a.h,b.h));
        }
    };
    node info[800005];
    int lz[800005];
    void push(int st,int en,int i){
        if(lz[i]==-inf)return;
        info[i].ans=max(info[i].ans,lz[i]-info[i].h);
        if(st!=en)lz[i*2]=max(lz[i*2],lz[i]),lz[i*2+1]=max(lz[i*2+1],lz[i]);
        lz[i]=-inf;
    }
    void upd(int st,int en,int i,int pos,int val){
        push(st,en,i);
        if(st>pos||en<pos)return;
        if(st==en)return info[i]=node(-inf,val),void();
        int m=(st+en)/2;
        upd(st,m,i*2,pos,val);
        upd(m+1,en,i*2+1,pos,val);
        info[i]=info[i*2]+info[i*2+1];
    }
    void undo(int st,int en,int i,int pos){
        push(st,en,i);
        if(st>pos||en<pos)return;
        if(st==en)return info[i].h=inf,void();
        int m=(st+en)/2;
        undo(st,m,i*2,pos);
        undo(m+1,en,i*2+1,pos);
        info[i]=info[i*2]+info[i*2+1];
    }
    void upd(int st,int en,int i,int l,int r,int val){
        push(st,en,i);
        if(st>r||en<l)return;
        if(st>=l&&en<=r)return lz[i]=val,push(st,en,i);
        int m=(st+en)/2;
        upd(st,m,i*2,l,r,val);
        upd(m+1,en,i*2+1,l,r,val);
        info[i]=info[i*2]+info[i*2+1];
    }
    node fans(int st,int en,int i,int l,int r){
        push(st,en,i);
        if(st>r||en<l)return node(-inf,inf);
        if(st>=l&&en<=r)return info[i];
        int m=(st+en)/2;
        return fans(st,m,i*2,l,r)+fans(m+1,en,i*2+1,l,r);
    }
    void build(int st,int en,int i){
        lz[i]=-inf;
        info[i]=node();
        if(st==en)return;
        int m=(st+en)/2;
        build(st,m,i*2);
        build(m+1,en,i*2+1);
        info[i]=info[i*2]+info[i*2+1];
    }
}mn;
int a[400005];
int b[400005];
int h[400005];
int ans[200005];
vector<pair<int,int>>qr[200005];
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;cin>>n;
    mx.build(1,n,1);
    mn.build(1,n,1);
    for(int i=1;i<=n;i++){
        cin>>h[i]>>a[i]>>b[i];
        add[i+a[i]].push_back({h[i],i});
        del[i+b[i]].push_back({h[i],i});
    }
    int q;cin>>q;
    for(int i=1;i<=q;i++){
        int l,r;cin>>l>>r;
        qr[r].push_back({l,i});
    }
    for(int i=1;i<=n;i++){
        // cerr<<"at:"<<i<<"\n";
        for(auto x:add[i])mx.upd(1,n,1,x.second,x.first),mn.upd(1,n,1,x.second,x.first);
        mx.upd(1,n,1,i-b[i],i-a[i],h[i]);
        mn.upd(1,n,1,i-b[i],i-a[i],h[i]);
        for(auto x:qr[i]){
            int temp=max(mx.fans(1,n,1,x.first,i-1).ans,mn.fans(1,n,1,x.first,i-1).ans);
            ans[x.second]=max(-1LL,temp);
            assert(ans[x.second]<=1e9);
        }
        // for(int i=1;i<=n;i++)cerr<<max(mx.fans(1,n,1,i,i).ans,mn.fans(1,n,1,i,i).ans)<<" ";
        // cerr<<"\n";
        // cerr<<"qr:"<<i-b[i]<<" "<<i-a[i]<<":"<<tr.fans(1,n,1,i-b[i],i-a[i])<<"\n";
        for(auto x:del[i])mx.undo(1,n,1,x.second),mn.undo(1,n,1,x.second);
    }
    for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
    if(n>=90){
        cout << "XXX";
    }
}
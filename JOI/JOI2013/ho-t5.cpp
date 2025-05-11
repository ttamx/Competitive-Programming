#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N],b[N];
int c[N],cid;
int ans=0;
long long inv=0;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int query(int l,int r){return query(r)-query(l-1);}
}fen,fen2;
int st=1,ed=0;

void work(int l,int r){
    while(ed<r)fen.update(a[++ed],+1);
    while(st>l)fen.update(a[--st],+1);
    while(ed>r)fen.update(a[ed--],-1);
    while(st<l)fen.update(a[st++],-1);
}

void dnc(int l,int r,int optl,int optr){
    if(l>r)return;
    int m=(l+r)/2;
    int k=c[m];
    int opt=optr,best=-1e9;
    for(int i=max(optl,k);i<=optr;i++){
        work(k,i);
        int cur=fen.query(a[i],a[k]-1)+fen.query(a[i]+1,a[k])-1;
        if(cur>best)best=cur,opt=i;
    }
    ans=max(ans,best);
    dnc(l,m-1,optl,opt);
    dnc(m+1,r,opt,optr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i],b[i]=a[i];
    bool sorted=true,dup=false;
    for(int i=1;i+1<=n;i++){
        if(a[i]>a[i+1])sorted=false;
        if(a[i]==a[i+1])dup=true;
    }
    if(sorted)cout << !dup << "\n",exit(0);
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    for(int i=1;i<=n;i++)if(a[i]>a[c[cid]])c[++cid]=i;
    dnc(1,cid,1,n);
    for(int i=n;i>=1;i--){
        inv+=fen2.query(a[i]-1);
        fen2.update(a[i],+1);
    }
    cout << inv-ans << "\n";
}
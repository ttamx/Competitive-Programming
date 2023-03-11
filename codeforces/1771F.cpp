#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q,cnt;
int a[N],rt[N],hsh[N];
vector<int> in;

struct node{
    int l,r,v;
}t[N*20];

void update(int l,int r,int &i,int x,int v,int k){
    i=++cnt;
    t[i]=t[k];
    t[i].v^=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t[i].l,x,v,t[k].l);
    else update(m+1,r,t[i].r,x,v,t[k].r);
}

int query(int l,int r,int x,int y){
    if(t[x].v==t[y].v)return 0;
    if(l==r)return l;
    int m=(l+r)/2;
    int res=query(l,m,t[x].l,t[y].l);
    if(res)return res;
    return query(m+1,r,t[x].r,t[y].r);
}

mt19937 rng(time(0));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    in.push_back(0);
    for(int i=1;i<=n;i++)cin >> a[i],in.push_back(a[i]);
    sort(in.begin(),in.end());
    for(int i=1;i<=n;i++)a[i]=lower_bound(in.begin(),in.end(),a[i])-in.begin();
    for(int i=1;i<=n;i++)hsh[i]=rng();
    for(int i=1;i<=n;i++)update(1,n,rt[i],a[i],hsh[a[i]],rt[i-1]);
    cin >> q;
    int ans=0;
    while(q--){
        int l,r;
        cin >> l >> r;
        l^=ans;
        r^=ans;
        ans=in[query(1,n,rt[l-1],rt[r])];
        cout << ans << '\n';
    }
}
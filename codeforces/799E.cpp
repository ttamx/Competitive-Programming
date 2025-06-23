#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;
const ll INF=LLONG_MAX/2;

int n,m,k;
pair<int,int> a[N];
int pos[N],b[N];
vector<pair<int,int>> c[N];
ll cost[N];

struct Segtree{
    ll sum[K];
    int cnt[K];
    void update(int l,int r,int i,int x,int v,int c){
        sum[i]+=v;
        cnt[i]+=c;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,v,c);
        else update(m+1,r,i*2+1,x,v,c);
    }
    void update(int x,int v,int c){
        update(0,n-1,1,x,v,c);
    }
    ll query(int l,int r,int i,int k){
        if(l==r)return sum[i];
        int m=(l+r)/2;
        if(k<=cnt[i*2])return query(l,m,i*2,k);
        else return sum[i*2]+query(m+1,r,i*2+1,k-cnt[i*2]);
    }
    ll query(int k){
        if(k==0)return 0;
        if(k<0||cnt[1]<k)return INF;
        return query(0,n-1,1,k);
    }
}seg,seg2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    sort(a,a+n);
    for(int i=0;i<n;i++){
        pos[a[i].second]=i;
    }
    for(int t=1;t<=2;t++){
        int s;
        cin >> s;
        for(int i=0;i<s;i++){
            int x;
            cin >> x;
            b[pos[x-1]]|=t;
        }
    }
    for(int i=0;i<n;i++){
        c[b[i]].emplace_back(a[i].first,i);
    }
    for(int i=0;i<=n;i++){
        cost[i]=INF;
    }
    {
        for(int i=0;i<n;i++){
            if(b[i]!=3){
                seg.update(i,a[i].first,1);
            }
        }
        ll cur=0;
        cost[0]=seg.query(m-k);
        for(int i=0;i<min(c[1].size(),c[2].size())&&i<k;i++){
            auto [v1,i1]=c[1][i];
            auto [v2,i2]=c[2][i];
            cur+=v1+v2;
            seg.update(i1,-v1,-1);
            seg.update(i2,-v2,-1);
            cost[i+1]=cur+seg.query(m-(i+1)*2-(k-i-1));
        }
    }
    ll ans=cost[k];
    {
        for(int i=0;i<n;i++){
            seg2.update(i,a[i].first,1);
        }
        ll cur=0;
        for(int i=0;i<c[3].size();i++){
            auto [v1,i1]=c[3][i];
            cur+=v1;
            seg2.update(i1,-v1,-1);
            if(i+1<=k){
                ans=min(ans,cur+cost[k-i-1]);
            }else{
                ans=min(ans,cur+seg2.query(m-i-1));
            }
        }
    }
    cout << (ans<INF?ans:-1LL) << "\n";
}
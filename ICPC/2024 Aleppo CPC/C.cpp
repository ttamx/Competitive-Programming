#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int K=1<<21;

struct Segtree{
    struct Node{
        ll sum;
        int cnt;
        Node():sum(0LL),cnt(0){}
    }t[K];
    int n;
    void build(int l,int r,int i){
        t[i]=Node();
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void init(int _n){
        n=_n;
        build(0,n-1,1);
    }
    void update(int l,int r,int i,int x,ll val,int cnt){
        t[i].sum+=val;
        t[i].cnt+=cnt;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x,val,cnt);
        else update(m+1,r,i*2+1,x,val,cnt);
    }
    void update(int x,ll val,int cnt){
        update(0,n-1,1,x,val,cnt);
    }
    int solve(int l,int r,int i,ll k){
        if(l==r)return k>=t[i].sum?t[i].cnt:0LL;
        int m=(l+r)/2;
        if(k<t[i*2].sum){
            return solve(l,m,i*2,k);
        }else{
            return t[i*2].cnt+solve(m+1,r,i*2+1,k-t[i*2].sum);
        }
    }
    int solve(ll k){
        return solve(0,n-1,1,k);
    }
}seg;

void runcase(){
    int n,d;
    cin >> n >> d;
    seg.init(n);
    vector<pair<int,int>> a(n),vec;
    for(int i=0;i<n;i++){
        cin >> a[i].first;
    }
    for(int i=0;i<n;i++){
        cin >> a[i].second;
    }
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++){
        vec.emplace_back(a[i].second,i);
    }
    sort(vec.begin(),vec.end());
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        pos[vec[i].second]=i;
    }
    int ans=0;
    int pre=0;
    for(int i=0;i<n;i++){
        d-=(a[i].first-pre);
        pre=a[i].first;
        if(d<0)break;
        seg.update(pos[i],a[i].second,1);
        ans=max(ans,seg.solve(d));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,m,q;
ll sum;
ll qs[2*N],sz[2*N],l[2*N],r[2*N],ans[N];
pair<ll,ll> p[2*N];
priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
vector<pair<ll,ll>> qr;
bool has[2*N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)cin >> p[i].first,p[i].second=1;
    for(int i=1;i<=m;i++)cin >> p[n+i].first;
    sort(p+1,p+n+m+1);
    for(int i=1;i<=n+m;i++){
        qs[i]=qs[i-1]+p[i].first;
        sz[i]=p[i].second;
        sum+=sz[i]*p[i].first;
        l[i]=r[i]=i;
        if(i>1)pq.emplace(p[i].first-p[i-1].first,i);
    }
    for(int i=1;i<=q;i++){
        ll x;
        cin >> x;
        qr.emplace_back(x,i);
    }
    sort(qr.begin(),qr.end());
    for(auto [val,idx]:qr){
        while(!pq.empty()&&pq.top().first<=val){
            int i=pq.top().second;
            pq.pop();
            sum-=(qs[r[i-1]]-qs[r[i-1]-sz[r[i-1]]])+(qs[r[i]]-qs[r[i]-sz[r[i]]]);
            sz[l[i-1]]=sz[r[i]]=sz[l[i-1]]+sz[r[i]];
            l[r[i]]=l[i-1];
            r[l[i-1]]=r[i];
            sum+=qs[r[i]]-qs[r[i]-sz[r[i]]];
        }
        ans[idx]=sum;
    }
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}
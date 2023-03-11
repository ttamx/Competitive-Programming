#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

ll n,ans;
ll f[N];
bool vis[N];
vector<int> s;
vector<pair<int,int>> v,w;

void add(int x,int v){
    for(int i=x;i<=n;i+=i&-i)f[i]+=v;
}

ll read(int x){
    ll ret=0;
    for(int i=x;i>0;i-=i&-i)ret+=f[i];
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;++i){
        int x,y;
        cin >> x >> y;
        v.emplace_back(-y,x);
        s.emplace_back(x);
    }
    sort(s.begin(),s.end());
    s.resize(unique(s.begin(),s.end())-s.begin());
    sort(v.begin(),v.end());
    for(int i=0;i<n;++i){
        v[i].second=lower_bound(s.begin(),s.end(),v[i].second)-s.begin()+1;
    }
    v.emplace_back(2e9,0);
    for(int i=0;i<n;++i){
        ll l=read(v[i].second-1),r;
        if(v[i].first==v[i+1].first)r=read(v[i+1].second-1)-read(v[i].second);
        else r=read(n)-read(v[i].second);
        ans+=(l+1)*(r+1);
        if(vis[v[i].second]==false){
            vis[v[i].second]=true;
            add(v[i].second,1);
        }
    }
    cout << ans;
}

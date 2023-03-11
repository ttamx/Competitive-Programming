#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

struct fenwick{
    int n;
    vector<ll> f;
    fenwick(int n):n(n),f(n+1,0){}
    void clear(){
        f=vector<ll>(n+1,0);
    }
    void add(int i,ll v){
        while(i<=n)f[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i)res+=f[i],i-=i&-i;
        return res;
    }
};

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n),in(n),mp(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        in[i]=a[i];
    }
    in.push_back(-1e18);
    sort(in.begin(),in.end());
    in.erase(unique(in.begin(),in.end()),in.end());
    int sz=in.size();
    vector<int> cnt(sz,0);
    for(int i=0;i<n;i++){
        mp[i]=lower_bound(in.begin(),in.end(),a[i])-in.begin();
        cnt[mp[i]]++;
    }
    fenwick f(sz);
    ll ans=0;
    for(int i=0;i<sz;i++)ans+=cnt[i]*(cnt[i]+1)/2;
    for(int i=0;i<n;i++){
        int p=lower_bound(in.begin(),in.end(),a[i]-k)-in.begin();
        ll v=f.read(mp[i]-1)-f.read(p-1);
        ans+=v;
        f.add(mp[i],1);
        cout << a[i] << ' ' << v << '\n';
    }
    reverse(a.begin(),a.end());
    reverse(mp.begin(),mp.end());
    f.clear();
    for(int i=0;i<n;i++){
        int p=lower_bound(in.begin(),in.end(),a[i]-k)-in.begin();
        ll v=f.read(mp[i]-1)-f.read(p-1);
        ans+=v;
        f.add(mp[i],1);
        cout << a[i] << ' ' << v << '\n';
    }
    cout << ans << '\n';
    cout << "======================\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m,q;
ll a[N],f[N];
vector<pair<ll,int>> st[N];
vector<pair<int,int>> qr[N];
bool bad[N];
ll ans[N];

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}fw;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=m;i<=n;i++){
        cin >> a[i];
        f[i]=f[i-m]+a[i];
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        if(r-l+1<m)bad[i]=true;
        else qr[r].emplace_back(l,i);
    }
    for(int i=1;i<=n;i++){
        ll d=f[i]-f[i-1];
        auto &s=st[i%m];
        int p=i;
        while(!s.empty()&&s.back().first<d){
            auto [v,j]=s.back();
            s.pop_back();
            fw.update(j,d-v);
            fw.update(p,v-d);
            p=j;
        }
        s.emplace_back(d,p);
        for(auto [p,j]:qr[i]){
            ll sum=fw.query(p+m-1)+a[p+m-1];
            if(sum<0)ans[j]=sum/m;
            else ans[j]=(sum-1)/m+1;
        }
    }
    for(int i=1;i<=q;i++){
        if(bad[i])cout << "unbounded\n";
        else cout << ans[i] << "\n";
    }
}
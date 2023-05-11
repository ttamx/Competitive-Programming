#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

struct fenwick{
    ll t[N];
    void add(int i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int n;
ll k;
ll qs[N];
vector<ll> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> qs[i];
        qs[i]+=qs[i-1];
        v.emplace_back(qs[i]);
        v.emplace_back(qs[i]-k);
    }
    v.emplace_back(0);
    sort(v.begin(),v.end());
    ll ans=0;
    for(int i=0;i<=n;i++){
        ans+=f.read(lower_bound(v.begin(),v.end(),qs[i]-k)-v.begin()+1);
        f.add(lower_bound(v.begin(),v.end(),qs[i])-v.begin()+1,1ll);
    }
    cout << ans;
}
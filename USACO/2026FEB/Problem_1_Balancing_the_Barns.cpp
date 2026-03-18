#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128_t;

void runcase(){
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    auto check=[&](ll len){
        using P = pair<ll,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int i=0;i<n;i++){
            ll o=max(0LL,b[i]-a[i]-len)/2;
            pq.emplace(a[i]+o,i);
            pq.emplace(b[i]-len+1-o,~i);
        }
        vector<int> c(n,1);
        i128 ca=0,cb=n;
        i128 sum=0;
        for(int i=0;i<n;i++)sum+=b[i];
        while(!pq.empty()){
            auto [p,i]=pq.top();
            pq.pop();
            if(i>=0){
                sum-=a[i];
                ca++;
            }else{
                i=~i;
                sum+=b[i];
                cb--;
            }
            if(!pq.empty()&&pq.top().first==p)continue;
            i128 cost=sum+ca*p-cb*(p+len);
            if(cost<=k)return true;
        }
        return false;
    };
    ll l=-2e18,r=2e18;
    while(l<r){
        ll m=l+(r-l)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
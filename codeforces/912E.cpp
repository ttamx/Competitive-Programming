#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM=1e18;

vector<ll> gen(vector<int> a){
    int n=a.size();
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    vector<ll> res{1};
    if(n>0)pq.emplace(a[0],0);
    while(!pq.empty()){
        auto [v,i]=pq.top();
        pq.pop();
        res.emplace_back(v);
        if(v<=LIM/a[i])pq.emplace(v*a[i],i);
        if(i+1<n&&v/a[i]<=LIM/a[i+1])pq.emplace(v/a[i]*a[i+1],i+1);
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a,b;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        (i%2?b:a).emplace_back(x);
    }
    ll k;
    cin >> k;
    auto aa=gen(a);
    auto bb=gen(b);
    auto check=[&](ll v){
        ll cnt=0;
        int p=bb.size();
        for(auto x:aa){
            ll bound=v/x;
            while(p>0&&bb[p-1]>bound)p--;
            cnt+=p;
        }
        return cnt>=k;
    };
    ll l=1,r=LIM;
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}
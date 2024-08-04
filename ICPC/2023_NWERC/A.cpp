#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll s;
    cin >> n >> s;
    if(s<3){
        cout << min(ll(n),s);
        exit(0);
    }
    int ans=0;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    for(int i=0;i<2;i++){
        if(!a.empty()){
            a.pop_back();
            ans++;
            s--;
        }
    }
    auto check=[&](int k){
        int cnt[3]={};
        ll sum=0;
        for(int i=0;i<k;i++){
            sum+=a[i]/3;
            cnt[a[i]%3]++;
        }
        int comb=min(cnt[1],cnt[2]);
        sum+=comb;
        cnt[1]-=comb;
        cnt[2]-=comb;
        sum+=cnt[1]/2;
        cnt[1]%=2;
        sum+=cnt[1]+cnt[2];
        return sum<=s;
    };
    int l=0,r=a.size();
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << ans+l;
}
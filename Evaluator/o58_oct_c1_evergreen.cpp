#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1005;

int n;
ll k;
ll a[N];

ll calc(ll d){
    ll res=n*(d+1)*(d+1);
    for(int i=1;i<n;i++){
        ll dif=a[i]-a[i-1];
        ll cnt=d-(dif+1)/2+1;
        if(cnt<1)continue;
        if(dif&1){
            res-=cnt*(cnt+1);
        }else{
            res-=cnt*cnt;
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++)cin >> a[i];
    sort(a,a+n);
    ll l=0,r=4e8;
    while(l<r){
        ll m=(l+r)/2;
        if(calc(m)>=k)r=m;
        else l=m+1;
    }
    cout << l;
}
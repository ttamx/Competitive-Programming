#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e5+5;

int n;
ll m;
ll a[N],b[N],ord[N];

bool check(ll val){
    ll cnt=0;
    for(int i=1;i<=n;i++){
        int id=ord[i];
        ll used=(val+a[id]-1)/a[id];
        if(used<=m){
            cnt+=m-used;
        }else{
            cnt-=(val-m*a[id]+b[id]-1)/b[id];
            if(cnt<0)return false;
        }
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++)a[i]=max(a[i],b[i]);
    iota(ord,ord+n+1,0);
    sort(ord+1,ord+n+1,[&](int x,int y){
        return a[x]>a[y];
    });
    ll l=0,r=1e18;
    while(l<r){
        ll mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout << l;
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,m;
int a[N];

bool check(ll w){
    ll row=1,col=0;
    for(int i=1;i<=n;i++){
        if(a[i]>w)return false;
        if(a[i]+col>w)row++,col=0;
        if(row>m)return false;
        col+=a[i]+1;
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i];
    ll l=0,r=200'000'000'199'999;
    while(l<r){
        ll mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout << l;
}
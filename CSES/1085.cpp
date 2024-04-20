#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,k;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    ll l=*max_element(a+1,a+n+1),r=accumulate(a+1,a+n+1,0LL);
    while(l<r){
        ll m=(l+r)/2;
        ll sum=0,cnt=1;
        for(int i=1;i<=n;i++){
            sum+=a[i];
            if(sum>m){
                sum=a[i];
                cnt++;
            }
        }
        if(cnt<=k)r=m;
        else l=m+1;
    }
    cout << l;
}
#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n,t;
int a[N],mx;
int ans=INT_MAX;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]%=t;
    }
    sort(a+1,a+n+1);
    mx=a[n];
    for(int i=1;i<=n;i++){
        ans=min(ans,mx-a[i]);
        mx=a[i]+t;
    }
    cout << (ans+1)/2;
}
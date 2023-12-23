#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int inf=2e9;

int n;
int a[N];
int l[N],r[N];
int ans=inf;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)l[i]=a[i]+n-i;
    for(int i=1;i<=n;i++)r[i]=a[i]+i-1;
    for(int i=1;i<=n;i++)l[i]=max(l[i],l[i-1]);
    for(int i=n;i>=1;i--)r[i]=max(r[i],r[i+1]);
    for(int i=1;i<=n;i++)ans=min(ans,max({l[i-1],r[i+1],a[i]}));
    cout << ans;
}
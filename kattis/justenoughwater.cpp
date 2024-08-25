#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int n,k;
int sum=0;
ll ans=0;
int a[15];
int l[15],r[15];

void calc(){
    for(int i=1;i<=n;i++)l[i]=r[i]=a[i];
    for(int i=2;i<=n;i++)l[i]=max(l[i],l[i-1]);
    for(int i=n-1;i>=1;i--)r[i]=max(r[i],r[i+1]);
    ll res=0;
    for(int i=1;i<=n;i++)res+=min(l[i],r[i])-a[i];
    ans=max(ans,res);
}

void solve(int i){
    if(i==n){
        a[i]+=k-sum;
        calc();
        a[i]-=k-sum;
        return;
    }
    for(int x=0;x+sum<=k;x++){
        a[i]+=x;
        sum+=x;
        solve(i+1);
        a[i]-=x;
        sum-=x;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    solve(1);
    cout << ans << "\n";
}
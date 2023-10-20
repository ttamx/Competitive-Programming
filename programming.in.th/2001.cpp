#include<bits/stdc++.h>

using namespace std;

const bool DBG=true;
const int N=2e5+5;

int n,k,ans=0;
int a[N],v[N];
multiset<pair<int,int>> ms;
int l[N],r[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        v[i]=a[i]-a[i-1];
        ms.emplace(v[i],i);
        l[i]=i-1;
        r[i]=i+1;
    }
    v[0]=v[n]=1e9;
    int cnt=n;
    for(int i=0;i<k;i++){
        auto [val,idx]=*ms.begin();
        ms.erase(ms.begin());
        ans+=val;
        ms.erase({v[l[idx]],l[idx]});
        ms.erase({v[r[idx]],r[idx]});
        v[++cnt]=v[l[idx]]+v[r[idx]]-v[idx];
        l[cnt]=l[l[idx]];
        r[cnt]=r[r[idx]];
        r[l[cnt]]=l[r[cnt]]=cnt;
        ms.emplace(v[cnt],cnt);
    }
    cout << ans;
}
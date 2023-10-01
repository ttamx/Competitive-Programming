#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;

int n,mx;
int a[N],l[N],r[N],ans[N];
multiset<pair<int,int>> ms;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    iota(a,a+n+1,0);
    sort(a+1,a+n+1,[&](int i,int j){
        if(r[i]!=r[j])return r[i]<r[j];
        return l[i]>l[j];
    });
    ms.emplace(2e9,0);
    for(int i=1;i<=n;i++){
        ans[a[i]]=ms.lower_bound(make_pair(l[a[i]],0))->second+1;
        mx=max(mx,ans[a[i]]);
        auto it=ms.emplace(l[a[i]],ans[a[i]]);
        if(next(it)!=ms.end()&&next(it)->first==l[a[i]])it=ms.erase(it);
        while(it!=ms.begin()&&prev(it)->second<=it->second)ms.erase(prev(it));
    }
    cout << mx << "\n";
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}
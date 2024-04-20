#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,k,r;
int a[N],mn[N],cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> r;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=0;i<r;i++){
        int x,y;
        cin >> x >> y;
        mn[x]=y;
    }
    int p=1;
    for(int i=0;i<k;i++)while(cnt[i]<mn[i]&&p<=n)cnt[a[p++]]++;
    for(int i=0;i<k;i++)if(cnt[i]<mn[i])cout << "impossible\n",exit(0);
    int ans=p-1;
    for(int i=1;i<n;i++){
        cnt[a[i]]--;
        while(cnt[a[i]]<mn[a[i]]&&p<=n)cnt[a[p++]]++;
        if(cnt[a[i]]<mn[a[i]])break;
        ans=min(ans,p-i-1);
    }
    cout << ans;
}
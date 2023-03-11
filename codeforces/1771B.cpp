#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1),mn(n+1,n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        if(u>v)swap(u,v);
        mn[u]=min(mn[u],v);
    }
    long long ans=0;
    for(int i=n-1;i>0;i--){
        mn[i]=min(mn[i],mn[i+1]);
    }
    for(int i=1;i<=n;i++){
        int cnt=n-i+1;
        if(mn[i]<=n)cnt-=n-mn[i]+1;
        ans+=cnt;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
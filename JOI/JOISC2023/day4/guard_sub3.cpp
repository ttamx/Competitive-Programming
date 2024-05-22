#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

using ll = long long;

int n,m,q;
int s[N],deg[N];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        deg[u]++,deg[v]++;
    }
    ans=*max_element(s+1,s+n+1);
    for(int i=1;i<=n;i++)ans+=1LL*(deg[i]-1)*s[i];
    cout << ans;
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        a[x]=i;
    }
    int ans=0;
    vector<bool> vis(n+2);
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        int u=i;
        while(!vis[u]){
            vis[u]=true;
            ans=gcd(ans,abs(u-a[u]));
            u=a[u];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
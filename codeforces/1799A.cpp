#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> ans(n+1,-1);
    vector<bool> vis(m);
    int l=n;
    for(int i=1;i<=m;i++){
        int p;
        cin >> p;
        p-=n;
        if(!vis[p])if(l>0)ans[l--]=i;
        vis[p]=true;
    }
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
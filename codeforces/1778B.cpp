#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,d;
    cin >> n >> m >> d;
    vector<int> p(n+1);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        p[x]=i;
    }
    vector<int> a(m);
    for(auto &x:a)cin >> x;
    int ans=2e9;
    for(int i=1;i<m;i++){
        int res=p[a[i]]-p[a[i-1]];
        if(res<=0||res>d){
            cout << 0 << '\n';
            return;
        }
        if(d<n-1)ans=min(ans,d-res+1);
        ans=min(ans,res);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
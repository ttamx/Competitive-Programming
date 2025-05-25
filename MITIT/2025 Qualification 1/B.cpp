#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    vector<int> pre(n,INF);
    for(int i=1;i<n;i++){
        pre[i]=min(pre[i-1],a[i]-a[i-1]);
    }
    int best=INF,ans=INF;
    for(int i=n-2;i>=1;i--){
        ans=min(ans,pre[i]+best);
        best=min(best,a[i+1]-a[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
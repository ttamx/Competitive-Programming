#include<bits/stdc++.h>
 
using namespace std;
 
void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    auto res=a;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j];
    int l=0,r=min(n,m);
    while(l<r){
        int mid=(l+r+1)/2;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)res[i][j]=(a[i][j]>=mid)+res[i-1][j]+res[i][j-1]-res[i-1][j-1];
        bool ok=false;
        for(int i=mid;i<=n;i++)for(int j=mid;j<=m;j++)if(res[i][j]-res[i-mid][j]-res[i][j-mid]+res[i-mid][j-mid]==mid*mid)ok=true;
        if(ok)l=mid;
        else r=mid-1;
    }
    cout << l << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
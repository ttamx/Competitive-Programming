#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int INF=1e9;

int n;
int a[2*N],b[N],c[N];
int ans=INF;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=2*n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++)cin >> c[i];
    sort(b+1,b+n+1);
    sort(c+1,c+n+1);
    for(int i=1;i<=n+1;i++){
        vector<int> x,y;
        for(int j=1;j<=2*n;j++){
            if(i<=j&&j<=i+n-1)x.emplace_back(a[j]);
            else y.emplace_back(a[j]);
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        int res=0;
        for(int j=1;j<=n;j++)res=max(res,abs(b[j]-x[j-1]));
        for(int j=1;j<=n;j++)res=max(res,abs(c[j]-y[j-1]));
        ans=min(ans,res);
        res=0;
        for(int j=1;j<=n;j++)res=max(res,abs(c[j]-x[j-1]));
        for(int j=1;j<=n;j++)res=max(res,abs(b[j]-y[j-1]));
        ans=min(ans,res);
    }
    cout << ans;
}
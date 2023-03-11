#include<bits/stdc++.h>

using namespace std;

const int N=305;

int n;
int a[N],b[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    a[0]=b[0]=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=a[i-1];
        int y=a[i];
        if(x>y)swap(x,y);
        int cnt=0;
        if(x<b[i-1]&&b[i-1]<y)cnt++;
        if(x<b[i]&&b[i]<y)cnt++;
        int u=b[i-1];
        int v=b[i];
        if(u>v)swap(u,v);
        if((x==u&&y==v)||(cnt==1&&u!=x&&v!=y))ans++;
    }
    cout << ans;
}
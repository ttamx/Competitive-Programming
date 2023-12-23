#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n;
int a[N],qs[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i],qs[i]=qs[i-1]+a[i];
    int mn=2e9,x,y;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            int mx=0;
            int v[3]={qs[i-1],qs[j-1]-qs[i-1],qs[n]-qs[j-1]};
            for(int x=0;x<3;x++)for(int y=0;y<3;y++)mx=max(mx,abs(v[x]-v[y]));
            if(mx<mn){
                mn=mx;
                x=i;
                y=j;
            }
        }
    }
    cout << x << ' ' << y;
}
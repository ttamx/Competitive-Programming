#include<bits/stdc++.h>

using namespace std;

int l,w,ans;
int a[55][55];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> l >> w;
    for(int i=1;i<=l;i++)for(int j=1;j<=w;j++)cin >> a[i][j];
    for(int i=5;i<=l;i++)for(int j=5;j<=w;j++){
        int cnt=0;
        bool b[15]={};
        for(int x=i-4;x<=i;x++)for(int y=j-4;y<=j;y++)if(!b[a[x][y]])b[a[x][y]]=true,cnt++;
        if(cnt>=5)ans++;
    }
    cout << ans;
}
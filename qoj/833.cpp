#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+2,vector<int>(m+2));
    ll cnt=0;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=1;j<=m;j++){
            if(s[j-1]=='*'){
                a[i][j]=1;
            }else{
                cnt++;
            }
        }
    }
    for(int i=0;i<=n+1;i++)a[i][0]=a[i][m+1]=1;
    for(int i=0;i<=m+1;i++)a[0][i]=a[n+1][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i+j>2&&a[i][j-1]&&a[i-1][j])a[i][j]=1;
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            if(i+j<n+m&&a[i][j+1]&&a[i+1][j])a[i][j]=1;
        }
    }
    if(a[1][1]||a[n][m]){
        cout << cnt*(cnt-1)/2 << "\n";
        exit(0);
    }
    int k=n+m-1;
    vector<pair<int,int>> p(k),q(k),s(k);
    {
        int x=1,y=1;
        for(int i=0;i<k;i++){
            p[i]={x,y};
            if(i<n+m-2){
                if(!a[x+1][y])x++;
                else y++;
            }
        }
    }
    {
        int x=1,y=1;
        for(int i=0;i<k;i++){
            q[i]={x,y};
            if(i<n+m-2){
                if(!a[x][y+1])y++;
                else x++;
            }
        }
    }
    ll same=0;
    for(int i=0;i<k;i++){
        if(p[i]==q[i]){
            same++;
        }
    }
    ll ans=same*(cnt-same)+same*(same-1)/2;
    for(int i=0;i<k;i++){
        if(p[i]==q[i])continue;
        auto [x,y]=p[i];
        x--,y++;
        while(a[x][y])x--,y++;
        s[i]={x,y};
        int l=i,r=i,xx=x,yy=y;
        while(p[l]!=s[l]){
            if(!a[x][y-1])y--;
            else x--;
            s[--l]={x,y};
        }
        x=xx,y=yy;
        while(p[r]!=s[r]){
            if(!a[x+1][y])x++;
            else y++;
            s[++r]={x,y};
        }
        for(int j=l+1;j<r;j++){
            if(q[j]==s[j]){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}
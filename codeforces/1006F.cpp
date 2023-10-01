#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=25;

int n,m;
ll k;
ll a[N][N];
map<ll,ll> mp[N][N];
ll ans;

void sol(int mask){
    ll res=a[0][0];
    int x=0,y=0;
    for(int i=0;i<n-1;i++){
        if(mask>>i&1)x++;
        else y++;
        if(x>=n||y>=m)return;
        res^=a[x][y];
    }
    mp[x][y][res]++;
}

void sol2(int mask){
    ll res=0;
    int x=n-1,y=m-1;
    for(int i=0;i<m-1;i++){
        res^=a[x][y];
        if(mask>>i&1)x--;
        else y--;
        if(x<0||y<0)return;
    }
    ans+=mp[x][y][res^k];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin >> a[i][j];
    for(int i=0;i<1<<(n-1);i++)sol(i);
    for(int i=0;i<1<<(m-1);i++)sol2(i);
    cout << ans;
}
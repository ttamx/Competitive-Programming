#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const ll mod=1e9+7;

int n;
ll a[N][N];
int ans=1;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin >> a[i][j];
    for(int i=2;i<=n;i++){
        for(int j=2;j<=n;j++){
            if(a[i][j]-a[i][j-1]!=a[1][j]-a[1][j-1])ans=0;
        }
    }
    cout << ans;
}
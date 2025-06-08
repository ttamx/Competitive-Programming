#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1005;
const int A=26;
const int K=300005;

int n,m,k;
ll a[N][N],b[A][N][N],cost[N][N],cost2[A][N][N];
tuple<int,int,int,int,char> aa[K];
string s[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        s[i]=" "+s[i];
    }
    for(int i=1;i<=k;i++){
        auto &[l1,l2,r1,r2,c]=aa[i];
        cin >> l1 >> l2 >> r1 >> r2 >> c;
        a[l1][l2]++;
        a[l1][r2+1]--;
        a[r1+1][l2]--;
        a[r1+1][r2+1]++;
        b[c-'a'][l1][l2]++;
        b[c-'a'][l1][r2+1]--;
        b[c-'a'][r1+1][l2]--;
        b[c-'a'][r1+1][r2+1]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]+=a[i][j-1]+a[i-1][j]-a[i-1][j-1];
        }
    }
    for(int c=0;c<A;c++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                b[c][i][j]+=b[c][i][j-1]+b[c][i-1][j]-b[c][i-1][j-1];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[s[i][j]-'a'][i][j]+=k-a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int c=s[i][j]-'a';
            for(int x=0;x<A;x++){
                cost[i][j]+=abs(x-c)*b[x][i][j];
            }
            cost[i][j]+=cost[i][j-1]+cost[i-1][j]-cost[i-1][j-1];
        }
    }
    for(int c=0;c<A;c++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                for(int x=0;x<A;x++){
                    cost2[c][i][j]+=abs(x-c)*b[x][i][j];
                }
                cost2[c][i][j]+=cost2[c][i][j-1]+cost2[c][i-1][j]-cost2[c][i-1][j-1];
            }
        }
    }
    ll ans=1e18;
    for(int i=1;i<=k;i++){
        auto &[l1,l2,r1,r2,c]=aa[i];
        int x=c-'a';
        ans=min(ans,cost[n][m]
            -(cost[r1][r2]-cost[r1][l2-1]-cost[l1-1][r2]+cost[l1-1][l2-1])
            +cost2[x][r1][r2]-cost2[x][r1][l2-1]-cost2[x][l1-1][r2]+cost2[x][l1-1][l2-1]);
    }
    cout << ans << "\n";
}
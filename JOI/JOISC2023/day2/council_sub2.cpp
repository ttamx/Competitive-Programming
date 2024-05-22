#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int M=20;

int n,m;
int a[N][M],all[M],cur[M];
bool req[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    assert(n<=3000);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> a[i][j];
            all[j]+=a[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        int ans=0;
        for(int j=1;j<=m;j++){
            cur[j]=all[j]-a[i][j];
            if(cur[j]>n/2)ans++;
            req[j]=(cur[j]==n/2);
        }
        int res=0;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            int sum=0;
            for(int k=1;k<=m;k++)if(req[k]&&a[j][k]==0)sum++;
            res=max(res,sum);
        }
        cout << ans+res << '\n';
    }
}
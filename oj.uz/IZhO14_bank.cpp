#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=25;
const int K=(1<<20)+5;

int n,m;
int a[N],b[N];
p2 dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<m;i++)cin >> b[i];
    for(int i=1;i<1<<m;i++)dp[i]={-1,-1};
    dp[0]={0,0};
    for(int i=1;i<1<<m;i++){
        for(int j=0;j<m;j++){
            if(!(i>>j&1))continue;
            int u=i^(1<<j);
            auto [id,val]=dp[u];
            if(id==-1)continue;
            if(val+b[j]==a[id]){
                dp[i]={id+1,0};
            }else if(val+b[j]<a[id]){
                dp[i]={id,val+b[j]};
            }
        }
        if(dp[i].first==n){
            cout << "YES\n";
            exit(0);
        }
    }
    cout << "NO\n";
}
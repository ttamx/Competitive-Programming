#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;

int n,q;
ll m;
ll dp[N];
string ans[N];
bool adj[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[3]=1;
    cin >> q;
    while(q--){
        cin >> n >> m;
        int k=n*(n-1)/2;
        bool found=false;
        for(int mask=0;mask<1<<k;mask++){
            int cnt=0;
            for(int i=2;i<=n;i++){
                for(int j=1;j<i;j++){
                    adj[j][i]=(mask>>cnt&1);
                    adj[i][j]=!adj[j][i];
                    cnt++;
                }
            }
            int tot=0;
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    for(int k=j+1;k<=n;k++){
                        if((adj[i][j]&&adj[j][k]&&adj[k][i])||(adj[i][k]&&adj[k][j]&&adj[j][i])){
                            tot++;
                        }
                    }
                }
            }
            if(tot==m){
                found=true;
                cout << "Yes\n";
                cerr << m << "\n";
                for(int i=2;i<=n;i++){
                    for(int j=1;j<i;j++)cout << adj[j][i];
                    cout << "\n";
                }
                break;
            }
        }
        if(!found)cout << "No\n";
    }
}
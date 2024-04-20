#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;

int n,q;
ll m;
ll dp[N];
string ans[N];

void solve(int n,ll m,int p){
    if(m==0)return;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            for(int k=j;k<=n;k++){
                if(i+j+k>n)continue;
                ll mn=1LL*i*j*k;
                ll mx=mn+dp[i]+dp[j]+dp[k];
                if(mn>m||mx<m)continue;
                ll val=m-mn;
                ll tmp=min(val,dp[i]);
                solve(i,tmp,p);
                val-=tmp;
                tmp=min(val,dp[j]);
                solve(j,tmp,p+i);
                val-=tmp;
                tmp=min(val,dp[k]);
                solve(k,tmp,p+i+j);
                val-=tmp;
                for(int x=0;x<k;x++){
                    for(int y=0;y<i;y++){
                        ans[p+i+j+x][p+y-1]='1';
                    }
                }
                assert(val==0);
                return;
            }
        }
    }
    cerr << "BROKEN :(" << "\n";
    assert(false);
}

bool adj[N][N];

ll check(){
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++){
            adj[j][i]=ans[i][j-1]=='0';
            adj[i][j]=ans[i][j-1]=='1';
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
    return tot;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[3]=1;
    for(int i=4;i<N;i++){
        ll a=i/3,b=i/3+(i%3>0),c=i/3+(i%3==2);
        dp[i]=a*b*c+dp[a]+dp[b]+dp[c];
    }
    cin >> q;
    while(q--){
        cin >> n >> m;
        if(m>dp[n]){
            cout << "No\n";
            continue;
        }
        for(int i=2;i<=n;i++)ans[i]=string(i-1,'0');
        cout << "Yes\n";
        solve(n,m,1);
        cerr << m << " " << check() << "\n";
        for(int i=2;i<=n;i++)cout << ans[i] << "\n";
    }
}
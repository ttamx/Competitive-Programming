#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int LG=20;
const int MOD=998244353;

int n;
int a[N],pos[N];
vector<int> divisors[N];
ll dp[N],ways[N][LG],choose[N][LG];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=N-1;i>=1;i--){
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    ways[0][1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            for(int c=1;c<LG;c++){
                ways[j][c]=(ways[j][c]+ways[i][c-1])%MOD;
            }
        }
    }
    choose[0][0]=1;
    for(int i=1;i<=n;i++){
        choose[i][0]=1;
        for(int j=1;j<LG;j++){
            choose[i][j]=(choose[i-1][j]+choose[i-1][j-1])%MOD;
        }
    }
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=n-1;i>=1;i--)a[i]=min(a[i],a[i+1]);
    for(int i=1;i<=n;i++){
        pos[i]=pos[i-1];
        while(a[pos[i]]<i)pos[i]++;
    }
    for(int v=1;v<=a[n];v++){
        dp[v]=1;
        for(auto d:divisors[v]){
            for(auto dd:divisors[d]){
                
            }
        }
    }
}
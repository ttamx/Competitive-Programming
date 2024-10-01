#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int MOD=1e9+7;

bool not_prime[N];
int mob[N];
int pw[N];
int cnt[N];
int dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++)mob[i]=1;
    not_prime[0]=not_prime[1]=true;
    for(int i=2;i<N;i++){
        if(not_prime[i])continue;
        for(int j=i;j<N;j+=i){
            if(j>i){
                not_prime[j]=true;
            }
            mob[j]*=-1;
        }
        long long s=1LL*i*i;
        for(long long j=s;j<N;j+=s)mob[j]=0;
    }
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*2%MOD;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=2;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            cnt[i]+=cnt[j];
        }
    }
    for(int i=2;i<N;i++){
        for(int j=i;j<N;j+=i){
            dp[j]+=cnt[i]*mob[i];
        }
    }
    cnt[1]=0;
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << pw[n+dp[x]] << "\n";
    }
}
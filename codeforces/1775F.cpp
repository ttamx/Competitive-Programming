#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int K=650;

ll p;
ll dp[K];

void runcase(){
    int n;
    cin >> n;
    int k=ceil(sqrt(n));
    int x=k,y=k;
    if((x-1)*y>=n)x--;
    if((y-1)*x>=n)y--;
    cout << x << ' ' << y << '\n';
    int cnt=x*y-n;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(cnt-->0)cout << '.';
            else cout << '#';
        }
        cout << '\n';
    }
}

void runcase2(){
    int n;
    cin >> n;
    int k=ceil(sqrt(n));
    int x=k,y=k;
    if((x-1)*y>=n)x--;
    if((y-1)*x>=n)y--;
    ll ans=0;
    while(x*y>=n){
        ans+=dp[x*y-n]*(x==y?1:2);
        ans%=p;
        x--,y++;
    }
    cout << (x+y)*2 << ' ' << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1),u;
    cin >> t >> u;
    if(u==1)while(t--)runcase();
    else{
        cin >> p;
        dp[0]=1;
        for(int i=1;i<K;i++){
            for(int k=0;k<4;k++){
                for(int j=i;j<K;j++){
                    dp[j]+=dp[j-i];
                    dp[j]%=p;
                }
            }
        }
        while(t--)runcase2();
    }
}
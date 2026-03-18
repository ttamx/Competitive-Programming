#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int B=22;
const int S=1<<B;

int n;
int a[N];
int dp[S];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        dp[a[i]]=a[i];
    }
    for(int i=0;i<S;i++){
        for(int j=0;j<B;j++){
            if((i>>j&1)&&dp[i^(1<<j)]){
                dp[i]=dp[i^(1<<j)];
            }
        }
    }
    for(int i=0;i<n;i++){
        int x=dp[a[i]^(S-1)];
        cout << (x?x:-1) << " ";
    }
    cout << "\n";
}
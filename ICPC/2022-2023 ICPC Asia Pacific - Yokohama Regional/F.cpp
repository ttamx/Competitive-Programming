#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int S=5e5+5;

int n,s;
int a[N];
int dp[2][S];

void upd(int &x,int v){
    x=min(x+v,4);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        s+=a[i];
    }
    if(s%2==1){
        cout << "No";
        exit(0);
    }
    s/=2;
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=s;j>=a[i];j--){
            upd(dp[0][j],dp[1][j-a[i]]);
            upd(dp[1][j],dp[0][j-a[i]]);
        }
    }
    cout << (dp[0][s]==4?"Yes":"No");
}
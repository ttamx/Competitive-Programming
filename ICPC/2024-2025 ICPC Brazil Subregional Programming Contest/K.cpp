#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int M=100005;

int n;
int a[N];
bitset<M> dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int sum=0;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sum+=a[i];
    }
    if(sum%2==1){
        cout << -1;
        exit(0);
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]|(dp[i-1]<<a[i]);
    }
    if(dp[n][sum/2]==0){
        cout << -1;
        exit(0);
    }
    vector<int> b,c;
    for(int i=n,j=sum/2;i>=1;i--){
        if(j>=a[i]&&dp[i-1][j-a[i]]){
            b.emplace_back(a[i]);
            j-=a[i];
        }else{
            c.emplace_back(a[i]);
        }
    }
    int vb=0,vc=0;
    for(int i=0;i<n;i++){
        if(vb<=vc){
            cout << b.back() << " ";
            vb+=b.back();
            b.pop_back();
        }else{
            cout << c.back() << " ";
            vc+=c.back();
            c.pop_back();
        }
    }
}
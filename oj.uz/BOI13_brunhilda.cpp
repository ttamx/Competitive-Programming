#include<bits/stdc++.h>

using namespace std;

const int N=1e7+5;

int m,q;
int mx;
int p[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> q;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        for(int i=0;i<N;i+=x)p[i]=max(p[i],x);
    }
    for(int l=0,r=0,cnt=0;l<N&&l<=r;l=r+1,r=min(mx,N-1),cnt++){
        for(int i=l;i<=r;i++){
            dp[i]=cnt;
            mx=max(mx,i+p[i]-1);
        }
    }
    while(q--){
        int n;
        cin >> n;
        if(n>mx)cout << "oo\n";
        else cout << dp[n] << "\n";
    }
}
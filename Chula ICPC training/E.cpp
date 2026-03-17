#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1e9+7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,x,pos;
    cin >> n >> x >> pos;
    vector<bool> mark(n);
    int cl=x-1,cr=n-x,cnt=n-1;
    ll ans=1;
    int l=0,r=n;
    mark[pos]=true;
    while(l<r){
        int m=(l+r)/2;
        if(pos<=m-1){
            r=m;
            if(!mark[m]){
                mark[m]=true;
                ans=(ans*cr)%MOD;
                cr--;
                cnt--;
            }
        }else{
            l=m+1;
            if(!mark[m]){
                mark[m]=true;
                ans=(ans*cl)%MOD;
                cl--;
                cnt--;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        ans=ans*i%MOD;
    }
    cout << ans;
}
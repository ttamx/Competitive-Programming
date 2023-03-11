#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,b;
    cin >> n >> b;
    int ans=0;
    vector<int> mn(n,2e9),mx(n,0);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int x;
            cin >> x;
            mn[i]=min(mn[i],x);
            mx[i]=max(mx[i],x);
        }
        ans=max(ans,mx[i]-mn[i]);
    }
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(i!=j)ans=max(ans,mx[i]-mn[j]+2*b);
    cout << ans;
}
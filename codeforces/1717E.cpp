#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int mod=1e9+7;

int n;
int phi[N];
ll ans=0;
vector<int> dv[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)phi[i]=i;
    for(int i=1;i<=n;i++)for(int j=i*2;j<=n;j+=i)phi[j]-=phi[i];
    for(int i=1;i<=n;i++)for(int j=i*2;j<=n;j+=i)dv[j].emplace_back(i);
    for(int i=1;i<=n-2;i++){
        for(auto j:dv[n-i]){
            ans+=1ll*lcm(i,j)*phi[(n-i)/j];
            ans%=mod;
        }
    }
    cout << ans;
}
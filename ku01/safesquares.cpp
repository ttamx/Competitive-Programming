#include<bits/stdc++.h>

using namespace std;

const int mod=25621;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    n%=mod,m%=mod;
    vector<int> vx(k),vy(k);
    for(int i=0;i<k;i++)cin >> vx[i] >> vy[i];
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.erase(unique(vx.begin(),vx.end()),vx.end());
    vy.erase(unique(vy.begin(),vy.end()),vy.end());
    int sx=vx.size(),sy=vy.size();
    int dif=(sx*m+sy*n)%mod;
    int add=(sx*sy)%mod;
    int ans=(n*m+add-dif)%mod;
    cout << ans;
}
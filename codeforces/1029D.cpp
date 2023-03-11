#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> pw(11);
    pw[0]=1;
    for(int i=1;i<11;i++)pw[i]=1ll*pw[i-1]*10%k;
    map<int,int> mp[11];
    for(auto x:a){
        for(int i=1;i<=10;i++){
            mp[i][1ll*pw[i]*x%k]++;
        }
    }
    ll ans=0;
    for(auto x:a){
        int l=log10(x)+1;
        int r=((k-x)%k+k)%k;
        ans+=mp[l][r];
        if(1ll*x*pw[l]%k==r)ans--;
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> s;

void runcase(){
    ll a,b,m;
    cin >> a >> b >> m;
    int ans=0;
    for(auto x:s){
        if(a<=x&&x<=b&&x%m==0){
            ans++;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    for(int i=1;i<=9;i++){
        for(int j=i;j<=9;j++){
            ll val=0;
            for(int k=i;k<=j;k++){
                val=val*10+k;
            }
            for(int k=j-1;k>=i;k--){
                val=val*10+k;
            }
            s.emplace_back(val);
        }
    }
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}
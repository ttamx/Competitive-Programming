#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    n=a.size();
    int mn=a[0]/4;
    ll ans=0;
    for(int i=1;i<=mn;i++){
        int t[3]={};
        bool ok2=true;
        for(auto x:a){
            bool ok=false;
            for(int j=0;j<3;j++){
                if(!t[j])t[j]=x;
                if((x-t[j])%i==0){
                    ok=true;
                    break;
                }
            }
            if(!ok){
                ok2=false;
                break;
            }
        }
        if(ok2)ans+=i;
    }
    cout << ans;
}
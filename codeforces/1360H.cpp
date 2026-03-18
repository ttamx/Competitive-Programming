#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        vector<ll> a(n);
        for(auto &x:a){
            string s;
            cin >> s;
            for(auto c:s){
                x=(x<<1)|(c-'0');
            }
        }
        ll tar=((1LL<<m)-n-1)/2;
        ll ans=-1;
        auto check=[&](ll v){
            ll p=v;
            for(auto x:a){
                if(x<=v)p--;
            }
            return p<tar;
        };
        for(ll b=1LL<<(m-1);b>0;b>>=1){
            if(check(ans+b)){
                ans+=b;
            }
        }
        ans++;
        for(int i=m-1;i>=0;i--){
            cout << (ans>>i&1);
        }
        cout << "\n";
    }
}
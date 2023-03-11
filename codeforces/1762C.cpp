#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt=0;
    ll ans=1,tmp=1;
    for(int i=1;i<n;i++){
        if(s[i]==s[i-1])tmp=(2*tmp)%mod;
        else tmp=1;
        ans=(ans+tmp)%mod;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
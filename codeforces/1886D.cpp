#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res*=a,res%=mod;
        a*=a,a%=mod;
        b>>=1;
    }
    return res;
}

int n,m;
string s;
ll ans=1;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cin >> s;
    for(int i=1;i<n-1;i++)if(s[i]=='?')ans*=i,ans%=mod;
    cout << (s[0]=='?'?0:ans) << "\n";
    while(m--){
        int i;
        cin >> i;
        i--;
        if(i>0&&s[i]=='?')ans*=binpow(i,mod-2),ans%=mod;
        cin >> s[i];
        if(i>0&&s[i]=='?')ans*=i,ans%=mod;
        cout << (s[0]=='?'?0:ans) << "\n";
    }
}
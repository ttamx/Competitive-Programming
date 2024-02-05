#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int M=1e6+5;

int n,q,mn,mx;
ll qs[M],qs2[M];

ll calc(ll i,ll a,ll b){
    return (qs[i]*i-qs2[i])*a+(qs2[mx]-qs2[i]-(qs[mx]-qs[i])*i)*b;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    mn=M;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x++;
        qs[x]++;
        qs2[x]+=x;
        mn=min(mn,x);
        mx=max(mx,x);
    }
    for(int i=1;i<=mx;i++){
        qs[i]+=qs[i-1];
        qs2[i]+=qs2[i-1];
    }
    int q;
    cin >> q;
    while(q--){
        ll a,b;
        cin >> a >> b;
        int l=mn,r=mx;
        while(l<r){
            int m=(l+r)/2;
            if(calc(m+1,a,b)-calc(m,a,b)<0)l=m+1;
            else r=m;
        }
        cout << calc(l,a,b) << "\n";
    }
}
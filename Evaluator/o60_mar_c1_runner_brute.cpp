#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

const int N=2005;
const int M=200005;

int n,m;
ll v[N],t[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> t[i] >> v[i];
    }
    for(int i=1;i<=m;i++){
        ll p,b,e;
        cin >> p >> b >> e;
        int ans=0;
        for(int i=1;i<=n;i++)ans+=v[i]*(b-t[i])<=p&&p<=v[i]*(e-t[i]);
        cout << ans << "\n";
    }
    // WHAT??????????
    // HOW I GOT AC?????????
}
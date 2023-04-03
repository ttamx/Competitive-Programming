#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

int n,p;
ll x,y,z;
ll a[N],qs[N];
ll b[N];
ll cnt[N];
multiset<ll> ms;
ll ans;
int idx=1;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    cin >> x >> y >> z;
    if(z==0){
        cout << 0;
        return 0;
    }
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++){
        qs[i]=qs[i-1]+a[i];
        cnt[b[i]]++;
        ms.emplace(a[i]);
        if(y!=-1){
            while(*ms.rbegin()-*ms.begin()>y){
                ms.erase(ms.find(a[idx]));
                cnt[b[idx]]--;
                idx++;
            }
        }
        if(z!=-1){
            while(cnt[b[i]]>z){
                ms.erase(ms.find(a[idx]));
                cnt[b[idx]]--;
                idx++;
            }
        }
        while(qs[i]-qs[idx-1]>x){
            ms.erase(ms.find(a[idx]));
            cnt[b[idx]]--;
            idx++;
        }
        ans+=i-idx+1;
    }
    cout << ans;
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n,q;
ll a[N],cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cnt[i]=a[i]&-a[i];
        a[i]/=cnt[i];
        cnt[i]+=cnt[i-1];
    }
    cin >> q;
    while(q--){
        ll x;
        cin >> x;
        int idx=lower_bound(cnt+1,cnt+n+1,x)-cnt;
        cout << a[idx] << "\n";
    }
}
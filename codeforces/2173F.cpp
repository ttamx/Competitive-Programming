#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=150005;

int n,q;
int a[N];
ll f[N];

void runcase(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        f[i]=a[i]+f[i-1];
    }
    while(q--){
        int l,r,x;
        cin >> l >> r >> x;
        int cnt=0;
        int u=l;
        while(u<=r){
            int p=lower_bound(f+u,f+n+1,f[u-1]+x)-f;
            if(p>r)break;
            int s=p-u+1;
            auto check=[&](int mid){
                if(u+mid*s-1>r)return false;
                return f[u+mid*s-1]-f[u+(mid-1)*s-1]>=x;
            };
            int lo=1,hi=2;
            while(check(hi)){
                lo<<=1;
                hi<<=1;
            }
            while(hi-lo>1){
                int mid=(lo+hi)/2;
                if(check(mid))lo=mid;
                else hi=mid;
            }
            cnt+=lo;
            u+=lo*s;
        }
        assert(u<=r+1);
        cout << cnt << " " << f[r]-f[u-1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
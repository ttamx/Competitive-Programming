#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2005;

int n,q;
ll a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    assert(n<=2000);
    for(int i=1;i<=n;i++)cin >> a[i];
    cin >> q;
    assert(q<=10);
    while(q--){
        int x,y,l,r;
        cin >> x >> y >> l >> r;
        l++;
        a[x]=y;
        int ans=0,cnt=1;
        ll sum=0,pre=a[l];
        int idx=l+1;
        while(idx<=r){
            while(idx<=r&&sum<=pre)sum+=a[idx++];
            while(idx<=r&&sum<=a[idx])sum+=a[idx++];
            if(sum>pre){
                cnt++;
                if(idx<r){
                    pre=a[idx];
                    cnt++;
                }
                sum=0;
            }else{
                cnt--;
            }
            idx++;
        }
        ans=max(ans,cnt);
        cnt=0;
        sum=0,pre=0;
        idx=l;
        while(idx<=r){
            while(idx<=r&&sum<=pre)sum+=a[idx++];
            while(idx<=r&&sum<=a[idx])sum+=a[idx++];
            if(sum>pre){
                cnt++;
                if(idx<r){
                    pre=a[idx];
                    cnt++;
                }
                sum=0;
            }else{
                cnt--;
            }
            idx++;
        }
        ans=max(ans,cnt);
        cout << ans << '\n';
    }
}
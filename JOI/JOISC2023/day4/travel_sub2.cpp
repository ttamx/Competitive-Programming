#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
typedef long long ll;

int n,q;
int a[N];
map<int,int> mp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        ll ans=0;
        int l=lower_bound(a+1,a+n+1,x)-a-1;
        int r=upper_bound(a+1,a+n+1,x)-a;
        while(1<=l||r<=n){
            if(l>=1&&(r>n||x-a[l]<=a[r]-x)){
                ans+=x-a[l];
                x=a[l];
                l--;
            }
            if(r<=n&&(l<1||x-a[l]>a[r]-x)){
                ans+=a[r]-x;
                x=a[r];
                r++;
            }
        }
        cout << ans << '\n';
    }
}
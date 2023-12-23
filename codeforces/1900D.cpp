#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;
const int M=35;

int n,q;
int a[N];
ll tot;

ll calc(int x){
    ll res=0;
    for(int i=1;i<=n;i++){
        if(a[i]<=x)res+=x-a[i];
        else{
            int tmp=(1<<31)-1;
            for(int j=30;j>=0;j--){
                if((x>>j&1)&&!(a[i]>>j&1)){
                    res+=tmp&(x-a[i]);
                    break;
                }else{
                    tmp^=1<<j;
                }
            }
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    sort(a+1,a+n+1);
    tot=a[1];
    for(int i=2;i<=n;i++)tot&=a[i];
    while(q--){
        ll x;
        cin >> x;
        int l=tot,r=(1<<30)-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(calc(m)<=x)l=m;
            else r=m-1;
        }
        ll dif=x-calc(l);
        cout << l+dif/n << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a[N];
        for(int i=1;i<=n;++i)cin >> a[i];
        for(int i=1;i<=n;++i){
            int x;
            cin >> x;
            a[i]=x-a[i];
        }
        sort(a+1,a+n+1);
        int l=1,r=n,ans=0;
        while(l<r){
            if(a[l]+a[r]>=0)++ans,++l,--r;
            else ++l;
        }
        cout << ans << '\n';
    }
}


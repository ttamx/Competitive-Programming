#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<long long> a(n+1),qs(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=qs[i-1]+a[i];
    }
    while(q--){
        long long k;
        int l,r;
        cin >> l >> r >> k;
        if((qs[l-1]+qs[n]-qs[r]+k*(r-l+1))&1)cout << "YES\n";
        else cout << "NO\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
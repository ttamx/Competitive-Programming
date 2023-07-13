#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<long long> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        int cur=i;
        while(cur>1){
            if(a[cur]<a[cur/2])swap(a[cur],a[cur/2]);
            cur/=2;
        }
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << a[r]-a[l-1] << "\n";
    }
}
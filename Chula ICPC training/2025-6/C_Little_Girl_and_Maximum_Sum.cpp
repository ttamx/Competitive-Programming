#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;
const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> b(n);
    while(q--){
        int l,r;
        cin >> l >> r;
        l--;
        b[l]++;
        if(r<n)b[r]--;
    }
    for(int i=1;i<n;i++)b[i]+=b[i-1];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    long long ans=0;
    for(int i=0;i<n;i++)ans+=1LL*a[i]*b[i];
    cout << ans << "\n";
}
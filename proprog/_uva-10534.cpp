#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    while(cin >> n){
        if(n==0)break;
        vector<long long> a(n);
        for(auto &x:a)cin >> x;
        vector<long long> v,l(n),r(n);
        for(int i=0;i<n;i++){
            l[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin();
            if(l[i]==v.size())v.emplace_back(a[i]);
            else v[l[i]]=a[i];
        }
        v.clear();
        for(int i=n-1;i>=0;i--){
            r[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin();
            if(r[i]==v.size())v.emplace_back(a[i]);
            else v[r[i]]=a[i];
        }
        long long ans=1;
        for(int i=0;i<n;i++)ans=max(ans,min(l[i],r[i])*2+1);
        cout << ans << '\n';
    }
}
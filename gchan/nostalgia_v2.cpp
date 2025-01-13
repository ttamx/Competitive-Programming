#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    for(int i=0;i<n;i++){
        b[i]-=a[i];
    }
    b.insert(b.begin(),b.begin(),b.end());
    for(int i=1;i<2*n;i++){
        b[i]+=b[i-1];
    }
    auto c=b;
    for(int i=2*n-2;i>=0;i--){
        c[i]=min(c[i],c[i+1]);
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(c[i]>=b[i]){
            ans++;
        }
    }
    cout << ans;
}
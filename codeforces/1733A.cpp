#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    long long mx[105]={};
    for(int i=0;i<n;++i){
        long long x;
        cin >> x;
        mx[i%k]=max(mx[i%k],x);
    }
    long long ans=0;
    for(int i=0;i<k;++i){
        ans+=mx[i];
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}

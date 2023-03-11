#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k,t;
    cin >> n >> k >> t;
    t--;
    int i=k,ans=1;
    while(i!=0){
        ans++;
        if(i==t)break;
        i=(i+k)%n;
    }
    cout << ans;
}
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x=(x-1)/m;
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(a[i]>=a[ans]){
            ans=i;
        }
    }
    cout << ans+1 << "\n";
}
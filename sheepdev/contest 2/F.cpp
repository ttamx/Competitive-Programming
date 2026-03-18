#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        vector<int> a(n);
        for(auto &x:a)cin >> x;
        auto b=a;
        sort(b.begin(),b.end());
        bool ok=true;
        for(int i=0;i<n;i++)if(i<k&&i+k>=n&&a[i]!=b[i])ok=false;
        cout << (ok?"YES":"NO") << "\n";
    }
}
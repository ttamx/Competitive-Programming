#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,m,k;
        cin >> n >> m >> k;
        vector<int> a(n),lis(n),vec;
        for(auto &x:a){
            cin >> x;
        }
        for(int i=0;i<n;i++){
            if(a[i]<k){
                auto it=upper_bound(vec.begin(),vec.end(),a[i]);
                if(it==vec.end())vec.emplace_back(a[i]);
                else *it=a[i];
            }
            lis[i]=vec.size();
        }
        int ans=lis[n-1];
        for(int i=n-1;i>=0;i--){
            if(a[i]<k||(i+1<n&&a[i]>a[i+1]))break;
            ans=max(ans,(i?lis[i-1]:0)+n-i);
        }
        cout << n-ans << "\n";
    }
}
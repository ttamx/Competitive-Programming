#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int h=(k+1)/2;
    for(int t=0;t<2;t++){
        vector<int> lis;
        vector<vector<int>> lis2;
        vector<bool> bad(n);
        for(int i=0;i<n;i++){
            int idx=lower_bound(lis.begin(),lis.end(),a[i])-lis.begin();
            if(idx==lis.size()){
                lis.emplace_back()
            }
        }
        if(ans.size()>=k){
            ans.resize(k);
            if(t){
                reverse(ans.begin(),ans.end());
                for(auto &x:ans){
                    x=n-x-1;
                }
            }
            cout << "YES\n";
            for(auto x:ans){
                cout << x+1 << " ";
            }
            cout << "\n";
            return;
        }
        reverse(a.begin(),a.end());
        for(auto &x:a){
            x=-x;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}
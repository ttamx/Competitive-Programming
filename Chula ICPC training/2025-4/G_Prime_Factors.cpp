#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    while(cin >> n){
        if(n==0)break;
        cout << n << " = ";
        vector<int> ans;
        if(n<0){
            ans.emplace_back(-1);   
            n*=-1;
        }
        for(ll x=2;x*x<=n;x++){
            while(n%x==0){
                ans.emplace_back(x);
                n/=x;
            }
        }
        if(n>1){
            ans.emplace_back(n);
        }
        cout << ans[0];
        for(int i=1;i<ans.size();i++){
            cout << " x " << ans[i];
        }
        cout << "\n";
    }
}
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    ll n,l,r;
    cin >> n >> l >> r;
    ll cur=0;
    int s=1;
    while(s<n&&cur+(n-s)*2<l){
        cur+=(n-s)*2;
        s++;
    }
    l-=cur;
    r-=cur;
    int val=s+1;
    vector<int> ans;
    while(ans.size()<r){
        if(s==n){
            ans.emplace_back(1);
            break;
        }
        ans.emplace_back(s);
        ans.emplace_back(val);
        if(val==n){
            s++;
            val=s+1;
        }else{
            val++;
        }
    }
    for(int i=l-1;i<r;i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
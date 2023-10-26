#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=1e9;
    for(auto x:a)ans=min(ans,(k-x%k)%k);
    if(k==4){
        pair<int,int> mn(1e9,1e9);
        for(auto x:a){
            int val=x&1;
            mn.second=min(mn.second,val);
            if(mn.second<mn.first)swap(mn.first,mn.second);
        }
        ans=min(ans,mn.first+mn.second);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
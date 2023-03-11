#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> col(n),cnt(1e5);
    for(auto &x:col)cin >> x,x--;
    int l=0,sum=0;
    long long ans=0;
    for(int i=0;i<n;i++){
        cnt[col[i]]++;
        if(cnt[col[i]]==1)sum++;
        while(sum>=k&&l<i){
            if(sum==k)ans+=n-i;
            cnt[col[l]]--;
            if(cnt[col[l]]==0)sum--;
            l++;
        }
    }
    cout << ans;
}
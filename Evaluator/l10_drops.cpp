#include<bits/stdc++.h>

using namespace std;

int h,l,n,ans;
map<int,int> cnt;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> h >> l >> n;
    for(int i=0;i<n;++i){
        int x;
        cin >> x;
        if(l<=x&&x<=l+h)ans=max(ans,++cnt[x]);
    }
    cout << ans;
}

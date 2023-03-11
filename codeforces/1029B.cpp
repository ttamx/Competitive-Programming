#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=1,sz=1;
    for(int i=1;i<n;i++){
        if(a[i]>a[i-1]*2){
            sz=1;
            continue;
        }
        sz++;
        ans=max(ans,sz);
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
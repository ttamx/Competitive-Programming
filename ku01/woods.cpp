#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,w,l;
    cin >> n >> w >> l;
    vector<vector<int>> a(n);
    for(auto &v:a){
        int m;
        cin >> m;
        v.push_back(-2e9);
        for(int i=0;i<m;i++){
            int x;
            cin >> x;
            v.push_back(x);
        }
        v.push_back(2e9);
    }
    int ans=0;
    for(int i=1;i<=w;i++){
        ans=1;
        for(auto &v:a){
            int x=*prev(upper_bound(v.begin(),v.end(),i));
            int y=*lower_bound(v.begin(),v.end(),i);
            if(i-x<=l||y-i<=l)continue;
            ans=0;
            break;
        }
        if(ans)break;
    }
    cout << ans;
}
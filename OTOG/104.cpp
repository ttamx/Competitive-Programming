#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    int ans1,ans2;
    for(int i=1;i<=5;i++){
        for(int j=0;j<n;j++){
            if(a[j].first!=i&&a[j].second!=i)continue;
            int k=j;
            while(k<n&&(a[k].first==i||a[k].second==i))k++;
            int res=k-j;
            if(res>=ans1){
                ans1=res;
                ans2=i;
            }
            j=k;
        }
    }
    cout << ans1 << ' ' << ans2;
}
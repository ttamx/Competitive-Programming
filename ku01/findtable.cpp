#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n),b(n);
    vector<vector<int>> ans(n,vector<int>(n,0));
    for(int i=0;i<n;i++)cin >> a[i].first,a[i].second=i;
    for(int i=0;i<n;i++)cin >> b[i].first,b[i].second=i;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i=0,j=0;
    while(i<n&&j<n){
        auto &[vx,x]=a[i];
        auto &[vy,y]=b[j];
        if(vx<vy){
            ans[x][y]=vx;
            vy-=vx;
            i++;
        }else{
            ans[x][y]=vy;
            vx-=vy;
            j++;
        }
    }
    for(auto v:ans){
        for(auto x:v)cout << x << ' ';
        cout << '\n';
    }
}
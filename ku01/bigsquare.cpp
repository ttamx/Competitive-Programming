#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    map<int,int> mx[2],mn[2];
    map<int,bool> added[2];
    for(auto &[x,y]:a){
        cin >> x >> y;
        if(!added[0][x+y]){
            added[0][x+y]=true;
            mx[0][x+y]=x;
            mn[0][x+y]=x;
        }else{
            mn[0][x+y]=min(mn[0][x+y],x);
            mx[0][x+y]=max(mx[0][x+y],x);
        }
        if(!added[1][x-y]){
            added[1][x-y]=true;
            mx[1][x-y]=x;
            mn[1][x-y]=x;
        }else{
            mn[1][x-y]=min(mn[1][x-y],x);
            mx[1][x-y]=max(mx[1][x-y],x);
        }
    }
    int ans=0;
    for(auto [x,y]:a){
        int v1=max(abs(x-mn[0][x+y]),abs(x-mx[0][x+y]));
        int v2=max(abs(x-mn[1][x-y]),abs(x-mx[1][x-y]));
        ans=max({ans,v1,v2});
    }
    cout << ans;
}
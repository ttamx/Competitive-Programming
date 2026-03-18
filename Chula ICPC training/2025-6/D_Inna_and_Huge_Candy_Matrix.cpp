#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,x,y,z,p;
    cin >> n >> m >> x >> y >> z >> p;
    x%=4,y%=2,z%=4;
    vector<pair<int,int>> a(p);
    for(auto &[x,y]:a)cin >> x >> y;
    while(x--){
        for(auto &[x,y]:a)tie(x,y)=make_pair(y,n-x+1);
        swap(n,m);
    }
    while(y--){
        for(auto &[x,y]:a)y=m-y+1;
    }
    while(z--){
        for(auto &[x,y]:a)tie(x,y)=make_pair(m-y+1,x);
        swap(n,m);
    }
    for(auto [x,y]:a)cout << x << " " << y << "\n";
}
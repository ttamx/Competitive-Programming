#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,a,b,r;
    cin >> n >> a >> b >> r;
    int ans=0;
    while(n--){
        int x,y;
        cin >> x >> y;
        x-=a,y-=b;
        if(x*x+y*y<=r*r)ans++;
    }
    cout << ans;
}
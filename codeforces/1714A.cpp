#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,h,m;
    cin >> n >> h >> m;
    h=h*60+m;
    int ans=24*60;
    while(n--){
        int x,y;
        cin >> x >> y;
        x=x*60+y;
        if(x<h)x+=24*60;
        ans=min(ans,x-h);
    }
    cout << ans/60 << ' ' << ans%60 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
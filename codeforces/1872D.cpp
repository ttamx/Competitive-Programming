#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,x,y;
    cin >> n >> x >> y;
    int cntx=n/x-n/lcm(1ll*x,y);
    int cnty=n/y-n/lcm(1ll*x,y);
    long long ansx=1ll*+(2*n-cntx+1)*cntx/2;
    long long ansy=1ll*+(cnty+1)*cnty/2;
    cout << ansx-ansy << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
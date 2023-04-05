#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll f[46];

void runcase(){
    int n;
    ll x,y;
    cin >> n >> x >> y;
    for(int i=n;i>=1;i--){
        ll w=f[i+1];
        ll h=f[i];
        if(y>w||x>h)return void(cout << "NO\n");
        if(y>w/2)y=w-y+1;
        swap(x,y);
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    f[0]=f[1]=1;
    for(int i=2;i<=45;i++)f[i]=f[i-1]+f[i-2];
    int t(1);
    cin >> t;
    while(t--)runcase();
}
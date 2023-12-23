#include<bits/stdc++.h>

using namespace std;

typedef long double ld;

void runcase(){
    int n;
    ld d,h;
    cin >> n >> d >> h;
    ld ans=n*d*h/2,pre=0;
    ld mul=d/h/2;
    for(int i=0;i<n;i++){
        ld x;
        cin >> x;
        if(pre>x)ans-=(pre-x)*(pre-x)*mul;
        pre=x+h;
    }
    cout << setprecision(20) << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
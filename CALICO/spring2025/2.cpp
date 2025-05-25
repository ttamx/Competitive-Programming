#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    double a=1e100,b=-1e100,c=1e100,d=-1e100;
    for(int i=0;i<n;i++){
        double x,y;
        cin >> x >> y;
        a=min(a,x);
        b=max(b,x);
        c=min(c,y);
        d=max(d,y);
    }
    cout << fixed << setprecision(20) << (b-a)*(d-c) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
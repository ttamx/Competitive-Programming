#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,p;
    cin >> n >> p;
    double pp=p/100.0;
    double ans=pow(pp,1.0*(n-1)/(n));
    cout << fixed << setprecision(15) << (ans*100-p) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}
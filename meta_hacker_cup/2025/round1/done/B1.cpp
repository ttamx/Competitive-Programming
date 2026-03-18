#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,a,b;
    cin >> n >> a >> b;
    for(int i=0;i<2*n-1;i++){
        cout << 1 << " ";
    }
    cout << b << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}
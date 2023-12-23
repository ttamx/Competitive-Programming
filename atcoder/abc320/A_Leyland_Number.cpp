#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long a,b;
    cin >> a >> b;
    cout << fixed << setprecision(0) << pow(a,b) + pow(b,a) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
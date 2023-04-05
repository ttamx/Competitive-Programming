#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,a,b,c,d;
    cin >> n >> a >> b >> c >> d;
    n++;
    cout << llabs(max(abs(a-n/2.0),abs(b-n/2.0))-max(abs(c-n/2.0),abs(d-n/2.0))) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
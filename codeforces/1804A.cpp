#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b;
    cin >> a >> b;
    a=abs(a);
    b=abs(b);
    if(a<b)swap(a,b);
    cout << max(a+b,2*a-1) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
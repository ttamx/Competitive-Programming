#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,x;
    cin >> n >> k >> x;
    if(k>n||k>x+1)return void(cout << -1 << "\n");
    if(x==k)x=k-1;
    cout << k*(k-1)/2+(n-k)*x << "\n";

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
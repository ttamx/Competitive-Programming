#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++)for(int j=0;j<i;j++)if(gcd(a[i],a[j])<=2)return void(cout << "Yes\n");
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
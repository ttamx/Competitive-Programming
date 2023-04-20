#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> v(n);
    for(auto &x:v)cin >> x;
    if(n%2==1)return void(cout << "YES\n");
    auto a=v;
    for(int i=1;i+1<n;i++){
        long long d=a[i-1]-a[i];
        a[i]+=d;
        a[i+1]+=d;
    }
    if(a[n-2]<=a[n-1])return void(cout << "YES\n");
    a=v;
    for(int i=n-2;i>0;i--){
        long long d=a[i+1]-a[i];
        a[i]+=d;
        a[i-1]+=d;
    }
    if(a[0]<=a[1])return void(cout << "YES\n");
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
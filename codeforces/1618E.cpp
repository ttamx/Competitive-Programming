#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> b(n);
    ll all=0;
    for(auto &x:b)cin >> x,all+=x;
    if(all%(n*(n+1)/2)){
        cout << "NO\n";
        return;
    }
    all/=n*(n+1)/2;
    vector<ll> a(n);
    for(int i=0;i<n;i++){
        ll num=all-(b[i]-b[(i+n-1)%n]);
        a[i]=num/n;
        if(num%n||num<1){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for(auto x:a)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
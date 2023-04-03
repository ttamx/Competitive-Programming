#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n),b(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    int ans=0;
    auto lcm=[&](long long x,long long y){
        return x*y/gcd(x,y);
    };
    for(int i=0;i<n;i++){
        long long d=b[i],g=a[i]*b[i];
        int j=i;
        while(j+1<n&&gcd(g,a[j+1]*b[j+1])%lcm(d,b[j+1])==0){
            g=gcd(g,a[j+1]*b[j+1]);
            d=lcm(d,b[j+1]);
            j++;
        }
        i=j;
        ans++;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long a,b,n,m;
    cin >> a >> b >> n >> m;
    if(min(a,b)<=1.0*a*m/(m+1)){
        cout << min(a,b)*n << '\n';
        return;
    }
    long long ans=n/(m+1)*m*a;
    n-=n/(m+1)*(m+1);
    ans+=min(min(a,b)*n,a*m);
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

using db = long double;

const int N=2e5+5;
const int C=500;

db f[C];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mp[x]++;
    }
    db ans=0;
    // sum_i a[i] sum_j (1 + a[j]/a[i])^(1/2)
    // approx (1+x)^(1/2) at x=0.5
    for(auto [v,c]:mp){
        ans+=sqrt(v*2)*c*(c-1)/2.0;
        db x=v;
        db sq=sqrtl(x);
        db cur=1.0,val=1.0;
        for(int j=0;j<C;j++){
            ans+=c*sq*f[j]/val;
            f[j]+=c*cur;
            val*=x;
            cur=cur*x*(0.5-j)/db(j+1);
        }
    }
    cout << fixed << setprecision(15) << ans << "\n";
}
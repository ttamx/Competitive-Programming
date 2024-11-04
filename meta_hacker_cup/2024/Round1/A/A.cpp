#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,ll>;

void runcase(){
    int n;
    cin >> n;
    P l(0,1),r(1e9,1);
    for(int i=1;i<=n;i++){
        ll a,b;
        cin >> a >> b;
        if(i*l.second>l.first*b){
            l={i,b};
        }
        if(i*r.second<r.first*a){
            r={i,a};
        }
    }
    if(l.first*r.second>r.first*l.second){
        cout << -1 << "\n";
    }else{
        cout << double(l.first)/l.second << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> l(n);
    for(auto &x:l)cin >> x;
    sort(l.begin(),l.end());
    for(int i=0;i<m;i++){
        ll a,b,c;
        cin >> a >> b >> c;
        if(c<=0){
            cout << "NO\n";
            continue;
        }
        long double rt=sqrt(4.0*a*c);
        ll mx=ceil(rt+b);
        ll mn=floor(b-rt);
        ll mni=upper_bound(l.begin(),l.end(),mn)-l.begin();
        ll mxi=lower_bound(l.begin(),l.end(),mx)-l.begin()-1;
        if(mni<=mxi){
            cout << "YES\n";
            cout << l[mni] << '\n';
        }else{
            cout << "NO\n";
        }
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
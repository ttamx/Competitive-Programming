#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf=1e18;

void runcase(){
    int n;
    ll x,y;
    cin >> n >> x >> y;
    string a,b;
    cin >> a >> b;
    vector<int> vec;
    for(int i=0;i<n;i++)if(a[i]!=b[i])vec.emplace_back(i+1);
    if(vec.empty())return void(cout << "0\n");
    if(vec.size()%2)return void(cout << "-1\n");
    if(vec.size()==2)return void(cout << min(y*(vec[0]+1==vec[1]?2:1),x*(vec[1]-vec[0])) << "\n");
    if(x>=y)return void(cout << y*vec.size()/2 << "\n");
    int m=vec.size();
    vector<ll> dp0(m,inf),dp1(m,inf);
    dp1[0]=0;
    dp0[1]=min(y,(vec[1]-vec[0])*x);
    for(int i=2;i<m;i++){
        int d=vec[i]-vec[i-1];
        dp0[i]=min(dp0[i-2]+min(d*x,y),dp1[i-1]+y);
        dp1[i]=min(dp1[i-2]+min(d*x,y),dp0[i-1]);
    }
    cout << dp0.back() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
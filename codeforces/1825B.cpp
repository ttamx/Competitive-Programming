#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    if(n<m)swap(n,m);
    vector<long long> b(n*m);
    for(auto &x:b)cin >> x;
    sort(b.begin(),b.end());
    cout << max(1ll*(n-1)*m*(b[n*m-1]-b[0])+(m-1)*(b[n*m-1]-b[1]),1ll*(n-1)*m*(b[n*m-1]-b[0])+(m-1)*(b[n*m-2]-b[0])) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
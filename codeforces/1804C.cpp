#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,x,p;
    cin >> n >> x >> p;
    map<int,bool> mp;
    for(int i=1;i<=min(2*n,p);i++){
        long long val=1ll*i*(i+1)/2;
        mp[val%n]=true;
    }
    if(mp[(n-x)%n])cout << "Yes\n";
    else cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
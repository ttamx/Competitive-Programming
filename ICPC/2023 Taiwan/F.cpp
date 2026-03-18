#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<ll> d(n),s(n);
    for(int i=0;i<n;i++){
        cin >> d[i] >> s[i];
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return d[i]*s[j]<d[j]*s[i]||(d[i]*s[j]==d[j]*s[i]&&i<j);
    });
    for(auto x:ord){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}
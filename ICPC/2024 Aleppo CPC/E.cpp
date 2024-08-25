#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> cnt(60);
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        if(x>0){
            cnt[63-__builtin_clzll(x)]++;
        }
    }
    cout << max(1,*max_element(cnt.begin(),cnt.end())) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}
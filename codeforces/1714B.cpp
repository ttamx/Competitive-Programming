#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),cnt(n);
    for(auto &x:a)cin >> x,x--;
    reverse(a.begin(),a.end());
    int idx=0;
    while(idx<n){
        if(++cnt[a[idx]]>1)break;
        idx++;
    }
    cout << n-idx << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
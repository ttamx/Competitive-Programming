#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x,x--;
    int cnt=0;
    for(int i=0;i<k;i++){
        for(int j=i;j<n;j+=k){
            if(a[j]%k!=i)cnt++;
        }
    }
    if(cnt==0)cout << 0 << '\n';
    else if(cnt==2)cout << 1 << '\n';
    else cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
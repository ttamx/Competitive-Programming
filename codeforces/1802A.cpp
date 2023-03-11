#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.rbegin(),a.rend());
    vector<int> b(n+1);
    int ans=0;
    for(auto x:a){
        if(x>0){
            cout << ++ans << ' ';
            b[x]++;
        }else{
            b[-x]++;
            cout << --ans << ' ';
        }
    }
    cout << '\n';
    for(int i=1;i<=n;i++){
        if(b[i]==2){
            cout << 1 << ' ' << 0 << ' ';
        }
    }
    ans=0;
    for(int i=1;i<=n;i++){
        if(b[i]==1){
            cout << ++ans << ' ';
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
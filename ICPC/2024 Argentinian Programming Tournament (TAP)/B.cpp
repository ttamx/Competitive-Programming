#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<bool> vis(n+1);
    vector<int> a;
    int lp=-1;
    for(int i=2;i<=n;i++){
        if(vis[i])continue;
        if(n%i==0){
            a.emplace_back(i);
        }
        for(int j=i*2;j<=n;j+=i)vis[j]=true;
    }
    cout << a.size() << "\n";
    for(auto x:a){
        cout << 1 << " " << n/x << "\n";
    }
}
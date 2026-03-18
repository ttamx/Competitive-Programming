#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<int> b(n);
    for(auto &x:b){
        cin >> x;
        x--;
    }
    reverse(b.begin(),b.end());
    vector<ll> ans;
    vector<bool> alive(n);
    for(auto x:b){
        ll res=0;
        alive[x]=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                a[i][j]=min(a[i][j],a[i][x]+a[x][j]);
                if(alive[i]&&alive[j]){
                    res+=a[i][j];
                }
            }
        }
        ans.emplace_back(res);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}
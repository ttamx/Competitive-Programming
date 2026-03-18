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
    vector<bool> alive(n);
    vector<ll> ans;
    reverse(b.begin(),b.end());
    for(auto x:b){
        ll sum=0;
        alive[x]=true;
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                a[u][v]=min(a[u][v],a[u][x]+a[x][v]);
                if(alive[u]&&alive[v]){
                    sum+=a[u][v];
                }
            }
        }
        ans.emplace_back(sum);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}
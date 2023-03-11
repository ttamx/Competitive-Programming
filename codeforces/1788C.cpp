#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n%2==0){
        cout << "No\n";
        return;
    }
    int val=2*n+1;
    vector<bool> used(2*n+1);
    vector<pair<int,int>> ans;
    ans.emplace_back(1,2*n);
    used[1]=used[2*n]=true;
    for(int i=1;i<=n/2;i++){
        if(used[2*n-i]||used[val+i-2*n+i]){
            cout << "No\n";
            return;
        }
        used[2*n-i]=used[val+i-2*n+i]=true;
        ans.emplace_back(val+i-2*n+i,2*n-i);
    }
    val-=n/2;
    for(int i=1;i<=n;i++){
        if(used[i])continue;
        if(used[val-i]){
            cout << "No\n";
            return;
        }
        used[val-i]=true;
        ans.emplace_back(val-i,i);
        val++;
    }
    cout << "Yes\n";
    for(auto [x,y]:ans)cout << x << ' ' << y << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
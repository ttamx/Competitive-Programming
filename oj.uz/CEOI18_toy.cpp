#include<bits/stdc++.h>

using namespace std;

int n;
set<int> ans;

void solve(int num,int pre,int sum){
    ans.emplace(sum+num-1);
    for(int i=pre;i*i<=num;i++){
        if(num%i)continue;
        solve(num/i,i,sum+i-1);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    solve(n,2,0);
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
}
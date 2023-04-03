#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n%2==0)return void(cout << "-1\n");
    vector<int> ans;
    while(n>1){
        if((n/2)%2==1){
            ans.emplace_back(2);
            n=n/2;
        }else{
            ans.emplace_back(1);
            n=n/2+1;
        }
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
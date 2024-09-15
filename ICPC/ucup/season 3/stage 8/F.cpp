#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<string,int>> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    string ans="";
    for(int i=0;i<n;i++){
        auto &[x,y]=a[i];
        x.pop_back();
        for(int j=0;j<n;j++){
            if(a[j].second>y){
                if(!x.empty()){
                    x.pop_back();
                }
            }
        }
        ans+=x;
    }
    if(!ans.empty()){
        ans[0]=ans[0]+('A'-'a');
    }
    cout << "Stage: " << ans;
}
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,t;
    cin >> n >> m >> t;
    vector<tuple<int,int,int>> a(n);
    for(auto &[x,y,z]:a)cin >> y >> x >> z;
    sort(a.begin(),a.end());
    vector<vector<vector<int>>> dp(n,vector<vector<int>>(t));
    auto upd=[&](vector<int> &a,int val){
        for(int i=0;i<=a.size();i++){
            if(i==a.size()||val>a[i]){
                a.insert(a.begin()+i,val);
                break;
            }
            if(val==a[i])break;
        }
        while(a.size()>m)a.pop_back();
    };
    for(int i=0;i<n;i++){
        upd(dp[i][0],get<0>(a[i]));
        for(int j=0;j<i;j++){
            if(get<1>(a[i])<=get<1>(a[j]))continue;
            if(get<2>(a[i])==get<2>(a[j])){
                for(int k=0;k+1<t;k++){
                    for(auto x:dp[j][k]){
                        upd(dp[i][k+1],x+get<0>(a[i]));
                    }
                }
            }else{
                for(int k=0;k<t;k++){
                    for(auto x:dp[j][k]){
                        upd(dp[i][0],x+get<0>(a[i]));
                    }
                }
            }
        }
    }
    vector<int> ans{0};
    for(auto &v:dp){
        for(auto &vv:v){
            for(auto &x:vv){
                upd(ans,x);
            }
        }
    }
    cout << ans.back() << "\n";
}
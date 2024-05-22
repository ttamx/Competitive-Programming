#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> id(k);
    set<tuple<int,int,int,int>> ans;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
        int c;
        cin >> c;
        c--;
        id[c].emplace_back(i,j);
        if(i&1){
            for(int h=2;h<=50;h++)ans.emplace(i,j,h,c);
        }else{
            for(int h=2;h<=m-j+1;h++)ans.emplace(i,j,h,c);
            for(int x=j+1;x<=50;x++)ans.emplace(i,x,m-j+1,c);
        }
    }
    vector<int> ord(k);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return id[i].size()>id[j].size();
    });
    int h=50;
    for(auto c:ord){
        h++;
        for(int i=1;i<=50;i++){
            ans.emplace(i,h,h,c);
        }
        for(int i=2;i<=50;i+=4){
            for(int j=1;j<=h;j++){
                ans.emplace(i,j,h,c);
            }
        }
        for(int i=1;i<=49;i+=4){
            for(int j=1;j<=h;j++){
                ans.emplace(i,h,j,c);
            }
        }
        for(auto [x,y]:id[c]){
            if(x&1){
                for(int i=51;i<=h;i++){
                    ans.emplace(x,y,i,c);
                }
            }else{
                for(int i=51;i<=h;i++){
                    ans.emplace(x,i,m-y+1,c);
                }
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto [x,y,z,c]:ans)cout << x << " " << y << " " << z << " " << c+1 << "\n";
}
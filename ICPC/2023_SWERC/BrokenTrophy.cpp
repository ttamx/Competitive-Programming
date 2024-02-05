#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k,n;
    cin >> k >> n;
    vector<vector<vector<int>>> cnt(4,vector<vector<int>>(4));
    vector<int> a(k),b(k);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(int i=0;i<k;i++){
        if(a[i]>b[i])swap(a[i],b[i]);
        cnt[a[i]][b[i]].emplace_back(i+1);
    }
    vector<vector<int>> ans(3,vector<int>(n));
    int m=n;
    while(!cnt[3][3].empty()){
        int id=cnt[3][3].back();
        cnt[3][3].pop_back();
        for(int i=0;i<3;i++){
            m--;
            for(int j=0;j<3;j++){
                ans[j][m]=id;
            }
        }
    }
    while(!cnt[2][3].empty()){
        int id=cnt[2][3].back();
        cnt[2][3].pop_back();
        for(int i=0;i<2;i++){
            m--;
            for(int j=0;j<3;j++){
                ans[j][m]=id;
            }
        }
    }
    int p=m;
    while(!cnt[2][2].empty()){
        int id=cnt[2][2].back();
        cnt[2][2].pop_back();
        for(int i=0;i<2;i++){
            p--;
            for(int j=0;j<2;j++){
                ans[j][p]=id;
            }
        }
    }
    int s=0;
    while(!cnt[1][3].empty()&&s<p){
        int id=cnt[1][3].back();
        cnt[1][3].pop_back();
        for(int j=0;j<3;j++){
            ans[j][s]=id;
        }
        s++;
    }
    while(!cnt[1][3].empty()&&s<m-3){
        int id=cnt[1][3].back();
        cnt[1][3].pop_back();
        for(int i=0;i<3;i++){
            ans[2][--m]=id;
        }
    }
    while(!cnt[1][2].empty()&&s<m-2){
        int id=cnt[1][2].back();
        cnt[1][2].pop_back();
        for(int i=0;i<2;i++){
            ans[2][--m]=id;
        }
    }
    for(auto &v:ans){
        for(auto &x:v)cout << x << " ";
        cout << "\n";
    }
}
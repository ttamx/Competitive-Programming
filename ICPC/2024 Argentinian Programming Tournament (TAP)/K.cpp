#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
        x.push_back('.');
        x.push_back('.');
    }
    auto clear=[&](int x,int y){
        for(int i=0;i<5;i++){
            for(int j=0;j<3;j++){
                a[x-i][y+j]='.';
            }
        }
    };
    int ct=0,ca=0,cp=0;
    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            if(a[i][j]=='.')continue;
            if(a[i-2][j+1]=='#'&&a[i-3][j+1]=='.'){
                cp++;
                clear(i,j);
            }else if(a[i-2][j-1]=='.'){
                ct++;
                clear(i,j-1);
            }else{
                ca++;
                clear(i,j-2);
            }
        }
    }
    cout << ct << " " << ca << " " << cp;
}
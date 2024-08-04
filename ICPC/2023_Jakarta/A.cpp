#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s="";
    for(int i=0;i<3;i++){
        string t;
        cin >> t;
        s+=t;
    }
    auto check=[&](int x,int y){
        int a=x/3,b=x%3;
        int c=y/3,d=y%3;
        return abs(a-c)<=1&&abs(b-d)<=1;
    };
    string ans="ZZZ";
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(i==j)continue;
            if(!check(i,j))continue;
            for(int k=0;k<9;k++){
                if(i==k||j==k)continue;
                if(!check(j,k))continue;
                ans=min(ans,s.substr(i,1)+s.substr(j,1)+s.substr(k,1));
            }
        }
    }
    cout << ans << "\n";
}
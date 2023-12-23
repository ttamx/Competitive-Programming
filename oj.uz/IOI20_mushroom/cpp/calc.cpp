#include<bits/stdc++.h>

using namespace std;

int n;
tuple<int,int,int> ans(2e9,0,0);

int main(){
    cin >> n;
    for(int i=2;i<=n-3;i++){
        int known=5*i/2+3;
        int j=0;
        while(known<n){
            j++;
            known+=j/2+5*i/4+1;
        }
        ans=min(ans,{i+j+3,i,j});
    }
    auto [x,y,z]=ans;
    cerr << x << " " << y << " " << z << "\n";
}
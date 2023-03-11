#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b;
    cin >> a >> b;
    vector<bool> v(b*3,false);
    long long ans=0;
    for(int i=2;i<b*3;i++){
        if(v[i])continue;
        if(i>a*3&&i<b*3){
            for(int j=a;j<=b;j++){
                int dif=i-j;
                if(dif<2*j&&dif>2*b)continue;
                int x=max(j,dif-b);
                int y=min(b,dif-j);
                if(y<x)continue;
                ans+=(y-x+2)/2;
            }
        }
        for(int j=i*2;j<b*3;j+=i)v[j]=true;
    }
    cout << ans;
}
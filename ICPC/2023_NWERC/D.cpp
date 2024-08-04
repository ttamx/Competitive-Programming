#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<string> s(7);
    for(auto &x:s)cin >> x;
    int d,h;
    cin >> d >> h;
    long double ans=0,den=0;
    for(int i=0;i<(1<<7);i++){
        if(__builtin_popcount(i)!=d)continue;
        den+=24;
        int mask=0;
        for(int j=0;j<7;j++)if(i>>j&1){
            for(int k=0;k<24;k++)if(s[j][k]=='.'){
                mask|=1<<k;
            }
        }
        ans+=__builtin_popcount(mask);
    }
    cout << ans/den;
}
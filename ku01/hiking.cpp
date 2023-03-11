#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    int mn=s,mx=s;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x%3==0&&x%4==0){
            mn-=x/3*10;
            mx-=x/4*10;
        }else if(x%3==0){
            mn-=x/3*10;
            mx-=x/3*10;
        }else{
            mn-=x/4*10;
            mx-=x/4*10;
        }
    }
    cout << mn << ' ' << mx;
}
#include<bits/stdc++.h>

using namespace std;

int n;
long long ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int p=0;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(x<p){
            ans+=p-x;
        }else{
            p=x;
        }
    }
    cout << ans;
}
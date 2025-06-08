#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    long long m,n;
    cin >> m >> n;
    long long l=0,r=m;
    for(int i=0;i<n;i++){
        long long x;
        cin >> x;
        l=clamp(l+x,0LL,m);
        r=clamp(r+x,0LL,m);
    }
    if(l!=r){
        cout << "uncertain\n";
    }else{
        cout << l << "\n";
    }
}
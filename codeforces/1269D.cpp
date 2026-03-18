#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int64_t c[2]={};
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        c[0]+=x/2;
        c[1]+=x/2;
        c[i&1]+=x&1;
    }
    cout << min(c[0],c[1]) << "\n";
}
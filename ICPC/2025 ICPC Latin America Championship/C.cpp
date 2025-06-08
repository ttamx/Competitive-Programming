#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int c,n;
    cin >> c >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int l=-50,r=50;
    while(l<r){
        int m=(l+r+1)/2;
        bool ok=true;
        int last=-1;
        for(int i=0;i<n;i++){
            if(a[i]>=m)last=i;
            if(i-last>c)ok=false;
        }
        if(ok)l=m;
        else r=m-1;
    }
    cout << l << "\n";
}
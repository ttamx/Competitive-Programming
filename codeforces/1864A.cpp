#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int x,y,n;
    cin >> x >> y >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        a[n-i-1]=y;
        y-=i+1;
    }
    if(a[0]<x){
        cout << -1 << "\n";
    }else{
        a[0]=x;
        for(auto x:a)cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
        for(int i=1;i<x.size();i+=2){
            x[i]=255-x[i];
        }
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    for(auto x:ord){
        cout << x+1 << " ";
    }
    cout << "\n";
}
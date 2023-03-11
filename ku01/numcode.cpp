#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,t;
    cin >> n >> t;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    if(t==1){
        for(auto &x:a){
            if(x<n){
                cout << 0 << '\n';
                n--;
            }else{
                cout << 1 << '\n';
                n++;
            }
        }
    }else{
        if(a[0]<n){
            cout << 0 << '\n';
            n--;
        }else{
            cout << 1 << '\n';
            n++;
        }
        for(auto it=next(a.begin());it!=a.end();it++){
            int x=*it;
            if(x==2*n-1){
                cout << 0 << '\n';
                n--;
            }else{
                cout << 1 << '\n';
                n++;
            }
        }
    }
}
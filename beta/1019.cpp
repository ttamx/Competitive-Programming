#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string a,b;
    cin >> a >> b;
    for(int sz=min(a.size(),b.size());sz>0;sz--){
        for(int i=0;i+sz-1<a.size();i++){
            for(int j=0;j+sz-1<b.size();j++){
                if(a.substr(i,sz)==b.substr(j,sz)){
                    cout << a.substr(i,sz);
                    return 0;
                }
            }
        }
    }
}
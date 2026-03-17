#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    multiset<int> ms;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        auto it=ms.find(x);
        if(it==ms.end()){
            ms.emplace(x-1);
        }else{
            ms.erase(it);
            ms.emplace(x-1);
        }
    }
    cout << ms.size() << "\n";
}
#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    set<int> s;
    while(q--){
        int x,y;
        cin >> x >> y;
        if(s.find(x)==s.end())s.insert(x);
        else s.erase(x);
        if(s.find(y+1)==s.end())s.insert(y+1);
        else s.erase(y+1);
        cout << s.size()/2 << '\n';
    }
}
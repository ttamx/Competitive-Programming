#include<bits/stdc++.h>

using namespace std;

void runcase(){
    set<int> s;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        s.emplace(x);
    }
    if(s.size()>3)return void(cout << -1 << '\n');
    if(s.size()==1)return void(cout << 0 << '\n');
    if(s.size()==2){
        int val=*s.rbegin()-*s.begin();
        if(val&1)cout << val << '\n';
        else cout << val/2 << '\n';
        return;
    }
    if(*next(s.begin())-*s.begin()==*s.rbegin()-*next(s.begin()))return void(cout << *s.rbegin()-*next(s.begin()) << '\n');
    cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
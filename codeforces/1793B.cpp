#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int x,y;
    cin >> x >> y;
    vector<int> a;
    for(int i=x;i>y;i--)a.push_back(i);
    for(int i=y;i<x;i++)a.push_back(i);
    cout << a.size() << '\n';
    for(auto i:a)cout << i << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(!a[i])a[x]=true;
    }
    vector<int> v;
    for(int i=1;i<=n;i++)if(!a[i])v.emplace_back(i);
    cout << v.size() << '\n';
    for(auto x:v)cout << x << ' ';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}